import assert from "node:assert/strict";
import test from "node:test";
import { fuxaDelegated, fuxaUpstreamPath } from "./fuxa-proxy.mjs";

test("FUXA-fliken översätts till rotadressen", () => {
  assert.equal(fuxaUpstreamPath("/fuxa/"), "/");
  assert.equal(fuxaUpstreamPath("/fuxa/editor?x=1"), "/editor?x=1");
  assert.equal(fuxaUpstreamPath("/socket.io/?EIO=4"), "/socket.io/?EIO=4");
});

test("FUXA-anrop under fliken skiljs från dashboardens api", () => {
  assert.equal(fuxaDelegated({ url: "/fuxa/", headers: {} }), true);
  assert.equal(fuxaDelegated({ url: "/socket.io/?EIO=4", headers: {} }), true);
  assert.equal(
    fuxaDelegated({ url: "/api/settings", headers: { referer: "http://127.0.0.1/fuxa/" } }),
    true,
  );
  assert.equal(
    fuxaDelegated({ url: "/api/live", headers: { referer: "http://127.0.0.1/" } }),
    false,
  );
});
