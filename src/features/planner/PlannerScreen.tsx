import React from 'react';
import { FlatList, Pressable, StyleSheet, Text, View } from 'react-native';
import { generateWeeklyPlan } from '../../../core/planGenerator.mjs';
import { Goal, Equipment } from '../../../core/models.mjs';
import { colors, spacing } from '../../shared/theme/tokens';

const sessions = generateWeeklyPlan({ goal: Goal.loseWeight, equipment: Equipment.none });

export function PlannerScreen() {
  return (
    <FlatList
      data={sessions}
      keyExtractor={(item) => item.day}
      contentContainerStyle={styles.list}
      renderItem={({ item }) => (
        <View style={styles.card}>
          <View>
            <Text style={styles.day}>{item.day}</Text>
            <Text style={styles.title}>{item.title}</Text>
            <Text style={styles.meta}>{item.durationMin} min  {item.intensity}</Text>
          </View>
          <Pressable style={styles.button}>
            <Text style={styles.buttonLabel}>{item.ctaLabel}</Text>
          </Pressable>
        </View>
      )}
      ListFooterComponent={
        <View style={styles.streakCard}>
          <Text style={styles.streakLabel}>Streak counter</Text>
          <Text style={styles.streakValue}>6 days</Text>
        </View>
      }
    />
  );
}

const styles = StyleSheet.create({
  list: { gap: spacing.s10, paddingBottom: spacing.s18 },
  card: { backgroundColor: colors.surface, borderRadius: 14, padding: spacing.s14, flexDirection: 'row', justifyContent: 'space-between', alignItems: 'center' },
  day: { fontSize: 13, fontWeight: '700', color: colors.muted },
  title: { fontSize: 18, fontWeight: '700', color: colors.text, marginTop: 2 },
  meta: { fontSize: 13, color: colors.muted, marginTop: 2 },
  button: { backgroundColor: colors.accent, borderRadius: 10, paddingVertical: spacing.s8, paddingHorizontal: spacing.s12 },
  buttonLabel: { color: '#FFF', fontWeight: '700' },
  streakCard: { backgroundColor: colors.streakBg, borderRadius: 14, padding: spacing.s14, marginTop: spacing.s12 },
  streakLabel: { color: colors.streakLabel, fontWeight: '600' },
  streakValue: { color: colors.streakValue, fontWeight: '800', fontSize: 24, marginTop: 4 }
});
