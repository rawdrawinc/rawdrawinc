import fs from 'node:fs';

const required = ['App.tsx', 'app.json', 'index.js', 'babel.config.js', 'tsconfig.json'];
const missing = required.filter((file) => !fs.existsSync(file));

if (missing.length > 0) {
  console.error(`Missing required scaffold files: ${missing.join(', ')}`);
  process.exit(1);
}

console.log('Offline Expo scaffold is present.');
console.log('Next step: run npm install in a network-enabled environment, then npm run ios.');
