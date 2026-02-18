import fs from 'node:fs';
import path from 'node:path';
import { execSync } from 'node:child_process';

const version = process.env.RD_FITZ_VERSION || new Date().toISOString().slice(0, 10);
const outDir = 'dist';
const artifactName = `rd-fitz-${version}.tar.gz`;
const artifactPath = path.join(outDir, artifactName);

if (!fs.existsSync(outDir)) {
  fs.mkdirSync(outDir, { recursive: true });
}

const include = [
  'App.tsx',
  'app.json',
  'babel.config.js',
  'index.js',
  'tsconfig.json',
  'src',
  'core',
  'services',
  'content',
  'assets',
  'docs',
  'preview',
  'README.md'
].filter((entry) => fs.existsSync(entry));

if (include.length === 0) {
  console.error('No files found for release artifact.');
  process.exit(1);
}

const tarArgs = include.map((entry) => `'${entry}'`).join(' ');
execSync(`tar -czf '${artifactPath}' ${tarArgs}`, { stdio: 'inherit', shell: '/bin/bash' });
console.log(`Created artifact at ${artifactPath}`);
