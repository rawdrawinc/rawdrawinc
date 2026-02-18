# RD FITZ My Gym Copilot

This repository includes an Expo iPhone build path and release artifact automation.

## Expo setup

1. `npm run install:expo:template`
2. `npm install` on a network enabled machine
3. `npm run ios` on macOS with Xcode installed

## Release artifact and GitHub release

1. `npm run release:artifact`
2. `npm run release:github`

`release:github` requires:

- git remote `origin` configured to GitHub
- GitHub CLI installed
- GitHub CLI authenticated

## Optional GitHub Actions release

A manual workflow is included at `.github/workflows/release-artifact.yml`.
Trigger it from Actions and provide a tag.
It generates `dist/*.tar.gz` and uploads to GitHub Releases.

## Offline checks

1. `npm run bootstrap:offline`
2. `npm test`
