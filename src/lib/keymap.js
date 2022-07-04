
import { writable } from 'svelte/store';
import keycodes from './keycodes.js';

export const Keymap = writable({
    layers: {
        "Default": [
            [keycodes.KC_A],[keycodes.KC_B],[keycodes.KC_D],
            [keycodes.KC_E],  [keycodes.KC_F]
        ],
        "League": [
            [0],[1],[2],
            [3],  [4]
        ],
        "Functions": [
            [0],[1],[2],
            [3],  [4]
        ],
    },
    order: ["Default", "Layer 1", "Layer 2", "Layer 3"],
});