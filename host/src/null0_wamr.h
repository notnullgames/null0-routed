// setup WAMR and trigger cart load
int null0_wamr_load() {
  return 0;
}

// triggers cart update
int null0_wamr_update() {
  // demo
  null0_clear(PNTR_BLACK);
  null0_draw_circle(320 / 2, 240 / 2, 100, PNTR_RED);
  return 0;
}
