/** @type {import('tailwindcss').Config} */
/** @type {import('tailwindcss').Config} */
module.exports = {
  content: ["./app/**/*.{js,ts,jsx,tsx,mdx}",
  "./pages/**/*.{js,ts,jsx,tsx,mdx}",
  "./components/**/*.{js,ts,jsx,tsx,mdx}",],
  theme: {
    extend: {
      backgroundImage: {
        'sky-gif' : "url('../assets/sky-clouds.gif')",
      },
      colors: {
        malibu: {
          50:  '#f7fcff', 
          100: '#f0faff', 
          200: '#d9f2fe', 
          300: '#c1eafe', 
          400: '#93dafd', 
          500: '#65cafc', 
          600: '#5bb6e3', 
          700: '#4c98bd', 
          800: '#3d7997', 
          900: '#31637b'
      }
      }
    },
  },
  plugins: [],
}