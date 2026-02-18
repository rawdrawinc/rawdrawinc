import fs from 'node:fs';

const templatePath = 'config/package.expo-template.json';
const outputPath = 'package.json';

const template = fs.readFileSync(templatePath, 'utf8');
fs.writeFileSync(outputPath, `${template}\n`);
console.log('Wrote Expo package.json from template. Run npm install in a network-enabled environment.');
