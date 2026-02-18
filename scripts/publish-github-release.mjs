import { execSync } from 'node:child_process';
import fs from 'node:fs';

const tag = process.env.RD_FITZ_TAG || `v${new Date().toISOString().slice(0, 10).replace(/-/g, '')}`;
const title = process.env.RD_FITZ_RELEASE_TITLE || `RD FITZ ${tag}`;
const notes = process.env.RD_FITZ_RELEASE_NOTES || 'RD FITZ release artifact.';

function run(cmd) {
  return execSync(cmd, { stdio: 'pipe', encoding: 'utf8' }).trim();
}

let remote;
try {
  remote = run('git remote get-url origin');
} catch {
  console.error('No git remote named origin is configured.');
  process.exit(1);
}

if (!remote.includes('github.com')) {
  console.error('Origin remote is not a GitHub repository URL.');
  process.exit(1);
}

const artifactFiles = fs.existsSync('dist')
  ? fs.readdirSync('dist').filter((f) => f.endsWith('.tar.gz')).map((f) => `dist/${f}`)
  : [];

if (artifactFiles.length === 0) {
  console.error('No artifact files in dist. Run npm run release:artifact first.');
  process.exit(1);
}

try {
  run('gh --version');
} catch {
  console.error('GitHub CLI is not installed.');
  process.exit(1);
}

try {
  run('gh auth status');
} catch {
  console.error('GitHub CLI is not authenticated. Run gh auth login.');
  process.exit(1);
}

const files = artifactFiles.map((f) => `'${f}'`).join(' ');
execSync(`gh release create '${tag}' ${files} --title '${title}' --notes '${notes}'`, {
  stdio: 'inherit',
  shell: '/bin/bash'
});

console.log(`Published release ${tag}`);
