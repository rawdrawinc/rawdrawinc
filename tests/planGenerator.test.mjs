import test from 'node:test';
import assert from 'node:assert/strict';
import { generateWeeklyPlan } from '../core/planGenerator.mjs';
import { Goal, Equipment } from '../core/models.mjs';

test('lose weight with no equipment has cardio and bodyweight minimums', () => {
  const plan = generateWeeklyPlan({ goal: Goal.loseWeight, equipment: Equipment.none });
  const cardioCount = plan.filter((x) => x.title === 'Cardio').length;
  const bodyweightCount = plan.filter((x) => x.title === 'Bodyweight strength').length;

  assert.equal(plan.length, 7);
  assert.ok(cardioCount >= 3);
  assert.ok(bodyweightCount >= 2);
  assert.ok(plan.every((p) => p.ctaLabel === 'Start workout'));
});
