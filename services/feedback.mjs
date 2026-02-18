export const feedbackProfiles = Object.freeze({
  reminder: {
    haptic: 'selection',
    sound: 'assets/sounds/reminder_soft.mp3'
  },
  milestone: {
    haptic: 'success',
    sound: 'assets/sounds/milestone_bright.mp3'
  },
  workoutComplete: {
    haptic: 'impactMedium',
    sound: 'assets/sounds/workout_done.mp3'
  }
});

export function getFeedbackProfile(eventName) {
  return feedbackProfiles[eventName] || null;
}
