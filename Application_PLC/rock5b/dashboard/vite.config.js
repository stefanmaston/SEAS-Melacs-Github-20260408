import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import { attachPlant } from "./server/plant.mjs";

function plantPlugin() {
  return {
    name: "melacs-plant",
    configureServer(server) {
      attachPlant(server.middlewares);
    },
    configurePreviewServer(server) {
      attachPlant(server.middlewares);
    },
  };
}

export default defineConfig({
  plugins: [react(), plantPlugin()],
  server: { host: true, port: 5173 },
});
