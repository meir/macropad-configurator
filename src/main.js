import App from './App.svelte'

// Imported through html file
// @ts-ignore
const theme = new Theme();
theme.install(document.body);
theme.start();

const app = new App({
  target: document.getElementById('app')
})

export default app
