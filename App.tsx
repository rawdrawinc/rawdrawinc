import React, { useState } from 'react';
import { SafeAreaView, StyleSheet, Text, View } from 'react-native';
import { PlannerScreen } from './src/features/planner/PlannerScreen';
import { SegmentedTabs } from './src/shared/ui/SegmentedTabs';
import { colors, spacing } from './src/shared/theme/tokens';

export default function App() {
  const [tab, setTab] = useState('Planner');

  return (
    <SafeAreaView style={styles.root}>
      <View style={styles.header}>
        <Text style={styles.title}>RD FITZ</Text>
        <Text style={styles.subtitle}>My Gym Copilot</Text>
      </View>
      <SegmentedTabs tabs={['Planner', 'Workouts', 'Progress']} active={tab} onChange={setTab} />
      {tab === 'Planner' ? (
        <PlannerScreen />
      ) : (
        <View style={styles.placeholderWrap}>
          <Text style={styles.placeholder}>Screen in progress</Text>
        </View>
      )}
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  root: { flex: 1, backgroundColor: colors.background, paddingHorizontal: spacing.s16 },
  header: { marginTop: spacing.s10, marginBottom: spacing.s18 },
  title: { fontSize: 30, fontWeight: '800', color: colors.text },
  subtitle: { fontSize: 16, color: colors.muted, marginTop: 2 },
  placeholderWrap: { flex: 1, alignItems: 'center', justifyContent: 'center' },
  placeholder: { fontSize: 16, color: colors.muted, fontWeight: '600' }
});
