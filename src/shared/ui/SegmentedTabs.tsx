import React from 'react';
import { Pressable, Text, View, StyleSheet } from 'react-native';
import { colors, spacing } from '../theme/tokens';

type Props = {
  tabs: string[];
  active: string;
  onChange: (tab: string) => void;
};

export function SegmentedTabs({ tabs, active, onChange }: Props) {
  return (
    <View style={styles.wrap}>
      {tabs.map((tab) => {
        const selected = tab === active;
        return (
          <Pressable key={tab} onPress={() => onChange(tab)} style={[styles.tab, selected && styles.active]}>
            <Text style={selected ? styles.activeText : styles.text}>{tab}</Text>
          </Pressable>
        );
      })}
    </View>
  );
}

const styles = StyleSheet.create({
  wrap: { flexDirection: 'row', backgroundColor: colors.surface, borderRadius: 16, padding: 6, marginBottom: spacing.s12 },
  tab: { flex: 1, alignItems: 'center', paddingVertical: spacing.s10, borderRadius: 12 },
  active: { backgroundColor: colors.accent },
  text: { color: colors.muted, fontWeight: '600' },
  activeText: { color: '#FFFFFF', fontWeight: '700' }
});
