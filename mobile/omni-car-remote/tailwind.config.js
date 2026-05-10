/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    './app/**/*.{js,jsx,ts,tsx}',
    './components/**/*.{js,jsx,ts,tsx}',
    './shared/**/*.{js,jsx,ts,tsx}',
    './tabs/**/*.{js,jsx,ts,tsx}',
  ],
  presets: [require('nativewind/preset')],
  theme: {
    extend: {
      fontFamily: {
        sans: ['RajdhaniRegular'],
        light: ['RajdhaniLight'],
        medium: ['RajdhaniMedium'],
        semibold: ['RajdhaniSemiBold'],
        bold: ['RajdhaniBold'],
        mono: ['ShareTechMonoRegular'],
      },

      colors: {
        background: '#0F172A',
        surface: '#1E293B',
        panel: '#334155',
        border: '#475569',
        primary: '#38BDF8',
        secondary: '#94A3B8',
        muted: '#64748B',
        danger: '#EF4444',
        dangerBackground: '#FF3B5C0A',
        textPrimary: '#F1F5F9',
        neonRed: '#FF3B5C',
        neonGreen: '#00FF88',
      },
      spacing: {
        inlinePadding: 16,
        blockPadding: 14,
        buttonGap: 6,
        dpadSize: 64,
        buttonPadding: 8,
        buttonBorderRadius: 8,
        articleBorderRadius: 10,
        contentSpacing: 9,
        dpadBorderRadius: 12,
        stopButtonPadding: 16,
        gap: 6,
        labelSpacing: 10,
        sectionSpacing: 14,
      },
    },
  },
  plugins: [],
};
