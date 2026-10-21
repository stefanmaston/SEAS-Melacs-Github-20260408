import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import { allowFuxaUpgrade, ensureAuth, routeProtected } from "./server/auth.mjs";
import { fuxaDelegated, proxyFuxa, proxyFuxaUpgrade, redirectFuxaRoot } from "./server/fuxa-proxy.mjs";
import { attachPlant } from "./server/plant.mjs";

function guard(req, res, next) {
  routeProtected(req, res).then((done) => {
    if (done || res.headersSent || res.writableEnded) return;
    next();
  }).catch(next);
}

function attachFuxa(server) {
  server.middlewares.use((req, res, next) => {
    if (!fuxaDelegated(req)) {
      next();
      return;
    }
    if (redirectFuxaRoot(req, res)) return;
    proxyFuxa(req, res);
  });
  server.httpServer?.on("upgrade", (req, socket, head) => {
    if (!fuxaDelegated(req) || !allowFuxaUpgrade(req)) return;
    proxyFuxaUpgrade(req, socket, head);
  });
}

function plantPlugin() {
  return {
    name: "melacs-plant",
    async configureServer(server) {
      await ensureAuth();
      server.middlewares.use(guard);
      attachFuxa(server);
      attachPlant(server.middlewares);
    },
    async configurePreviewServer(server) {
      await ensureAuth();
      server.middlewares.use(guard);
      attachFuxa(server);
      attachPlant(server.middlewares);
    },
  };
}

export default defineConfig({
  plugins: [react(), plantPlugin()],
  server: { host: true, port: 5173 },
});
