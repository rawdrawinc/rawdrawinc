import test from 'node:test';
import assert from 'node:assert/strict';
import { detectMilestones } from '../core/milestones.mjs';

test('detects newly unlocked milestones without duplicates', () => {
  const stats = {
    workoutCount: 10,
    runCount: 5,
    strengthGainPercent: 6,
    streakDays: 8
  };

  const unlocked = detectMilestones(stats, ['first_workout']);

  assert.equal(unlocked.some((m) => m.id === 'first_workout'), false);
  assert.equal(unlocked.some((m) => m.id === 'five_runs'), true);
  assert.equal(unlocked.some((m) => m.id === 'ten_workouts'), true);
  assert.equal(unlocked.some((m) => m.id === 'strength_plus_five'), true);
  assert.equal(unlocked.some((m) => m.id === 'seven_day_streak'), true);
});
