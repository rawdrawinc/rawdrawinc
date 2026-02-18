export const MILESTONES = Object.freeze([
  { id: 'first_workout', title: 'First workout', check: (s) => s.workoutCount >= 1 },
  { id: 'five_runs', title: 'Five runs', check: (s) => s.runCount >= 5 },
  { id: 'ten_workouts', title: 'Ten workouts', check: (s) => s.workoutCount >= 10 },
  { id: 'strength_plus_five', title: 'Strength gain five percent', check: (s) => s.strengthGainPercent >= 5 },
  { id: 'seven_day_streak', title: 'Seven day streak', check: (s) => s.streakDays >= 7 }
]);

export function detectMilestones(stats, unlockedIds = []) {
  const unlockedSet = new Set(unlockedIds);
  return MILESTONES.filter((milestone) => !unlockedSet.has(milestone.id) && milestone.check(stats));
}
