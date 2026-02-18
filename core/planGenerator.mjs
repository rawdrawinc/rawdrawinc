import { Goal, Equipment, Intensity } from './models.mjs';

const CARDIO = { type: 'Cardio', durationMin: 35, intensity: Intensity.medium };
const BODYWEIGHT = { type: 'Bodyweight strength', durationMin: 30, intensity: Intensity.medium };
const RECOVERY = { type: 'Mobility recovery', durationMin: 20, intensity: Intensity.low };
const STRENGTH = { type: 'Strength', durationMin: 45, intensity: Intensity.high };

const DAY_NAMES = ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun'];

export function generateWeeklyPlan({ goal, equipment }) {
  if (!goal || !equipment) {
    throw new Error('Goal and equipment are required');
  }

  if (goal === Goal.loseWeight && equipment === Equipment.none) {
    const template = [CARDIO, BODYWEIGHT, CARDIO, RECOVERY, BODYWEIGHT, CARDIO, RECOVERY];
    return template.map((session, index) => mapSession(index, session));
  }

  if (goal === Goal.buildStrength) {
    const template = [STRENGTH, RECOVERY, STRENGTH, CARDIO, STRENGTH, BODYWEIGHT, RECOVERY];
    return template.map((session, index) => mapSession(index, session));
  }

  const template = [CARDIO, BODYWEIGHT, CARDIO, RECOVERY, CARDIO, BODYWEIGHT, RECOVERY];
  return template.map((session, index) => mapSession(index, session));
}

function mapSession(index, session) {
  return {
    day: DAY_NAMES[index],
    title: session.type,
    durationMin: session.durationMin,
    intensity: session.intensity,
    ctaLabel: 'Start workout'
  };
}

export function generateFourWeekPlan(input) {
  return Array.from({ length: 4 }, (_, weekIndex) => ({
    week: weekIndex + 1,
    sessions: generateWeeklyPlan(input)
  }));
}
