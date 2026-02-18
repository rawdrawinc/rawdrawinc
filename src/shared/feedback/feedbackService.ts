import * as Haptics from 'expo-haptics';
import { Audio } from 'expo-av';
import { getFeedbackProfile } from '../../../services/feedback.mjs';

export async function triggerFeedback(eventName: 'reminder' | 'milestone' | 'workoutComplete') {
  const profile = getFeedbackProfile(eventName);
  if (!profile) {
    return;
  }

  if (profile.haptic === 'success') {
    await Haptics.notificationAsync(Haptics.NotificationFeedbackType.Success);
  } else if (profile.haptic === 'selection') {
    await Haptics.selectionAsync();
  } else {
    await Haptics.impactAsync(Haptics.ImpactFeedbackStyle.Medium);
  }

  const { sound } = await Audio.Sound.createAsync({ uri: profile.sound });
  await sound.playAsync();
}
