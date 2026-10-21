import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import { attachEditor } from "./server/api.mjs";

function editorPlugin() {
  return {
    name: "melacs-editor",
    configureServer(server) {
      attachEditor(server.middlewares);
    },
  };
}

export default defineConfig({
  plugins: [react(), editorPlugin()],
  server: { host: "127.0.0.1", port: 5174 },
});
