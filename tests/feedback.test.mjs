import test from 'node:test';
import assert from 'node:assert/strict';
import { getFeedbackProfile } from '../services/feedback.mjs';

test('feedback profiles include milestone event', () => {
  const profile = getFeedbackProfile('milestone');
  assert.equal(profile.haptic, 'success');
  assert.ok(profile.sound.includes('milestone_bright.mp3'));
});
