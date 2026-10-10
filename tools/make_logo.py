import math, sys
cx, cy, a, n = 512, 500, 412, 5.0
pts = []
for i in range(256):
    t = 2 * math.pi * i / 256
    c, s = math.cos(t), math.sin(t)
    pts.append((cx + a * math.copysign(abs(c) ** (2 / n), c), cy + a * math.copysign(abs(s) ** (2 / n), s)))
squircle = "M" + " L".join(f"{x:.1f},{y:.1f}" for x, y in pts) + " Z"

# isometrischer Würfel
k = math.cos(math.radians(30))
s, ox, oy = 210, 512, 520
P = lambda x, y: f"{x:.1f},{y:.1f}"
top = [P(ox, oy - s), P(ox + s * k, oy - s / 2), P(ox, oy), P(ox - s * k, oy - s / 2)]
left = [P(ox - s * k, oy - s / 2), P(ox, oy), P(ox, oy + s), P(ox - s * k, oy + s / 2)]
right = [P(ox, oy), P(ox + s * k, oy - s / 2), P(ox + s * k, oy + s / 2), P(ox, oy + s)]
# Skizzen-Raute auf dem Boden
gx, gy, f = ox, oy + s / 2, 1.55
sk = [(gx, gy - s / 2 * f), (gx + s * k * f, gy), (gx, gy + s / 2 * f), (gx - s * k * f, gy)]
grid = "".join(f'<line x1="{x}" y1="0" x2="{x}" y2="1024"/>' for x in range(64, 1024, 64)) + \
       "".join(f'<line x1="0" y1="{y}" x2="1024" y2="{y}"/>' for y in range(64, 1024, 64))
poly = lambda p: " ".join(p)
svg = f'''<svg xmlns="http://www.w3.org/2000/svg" width="1024" height="1024" viewBox="0 0 1024 1024">
  <defs>
    <linearGradient id="bg" x1="0" y1="0" x2="0" y2="1">
      <stop offset="0" stop-color="#5DA2FF"/><stop offset="0.55" stop-color="#3D6BF2"/><stop offset="1" stop-color="#2B36C9"/>
    </linearGradient>
    <radialGradient id="glow" cx="0.5" cy="0.05" r="0.75">
      <stop offset="0" stop-color="#FFFFFF" stop-opacity="0.35"/><stop offset="1" stop-color="#FFFFFF" stop-opacity="0"/>
    </radialGradient>
    <linearGradient id="top" x1="0" y1="0" x2="0" y2="1">
      <stop offset="0" stop-color="#FFFFFF"/><stop offset="1" stop-color="#E4EDFF"/>
    </linearGradient>
    <linearGradient id="left" x1="0" y1="0" x2="1" y2="1">
      <stop offset="0" stop-color="#D3E1FF"/><stop offset="1" stop-color="#AFC4FF"/>
    </linearGradient>
    <linearGradient id="right" x1="1" y1="0" x2="0" y2="1">
      <stop offset="0" stop-color="#A9BEFF"/><stop offset="1" stop-color="#7E95F4"/>
    </linearGradient>
    <linearGradient id="sheen" x1="0" y1="0" x2="0" y2="1">
      <stop offset="0" stop-color="#FFFFFF" stop-opacity="0.22"/><stop offset="0.5" stop-color="#FFFFFF" stop-opacity="0"/>
    </linearGradient>
    <filter id="drop" x="-10%" y="-10%" width="120%" height="120%"><feGaussianBlur stdDeviation="14"/></filter>
    <filter id="soft" x="-50%" y="-50%" width="200%" height="200%"><feGaussianBlur stdDeviation="22"/></filter>
  </defs>
  <path d="{squircle}" fill="#0B1450" opacity="0.32" transform="translate(0 14)" filter="url(#drop)"/>
  <path d="{squircle}" fill="url(#bg)"/>
  <g>
    <path d="{squircle}" fill="url(#glow)"/>
    <g stroke="#FFFFFF" stroke-opacity="0.08" stroke-width="2">{grid}</g>
    <polygon points="{poly(P(*p) for p in sk)}" fill="#FFFFFF" fill-opacity="0.08" stroke="#FFFFFF" stroke-opacity="0.75"
             stroke-width="7" stroke-dasharray="26 18" stroke-linejoin="round"/>
    {"".join(f'<circle cx="{x:.1f}" cy="{y:.1f}" r="13" fill="#FFFFFF"/>' for x, y in sk)}
    <ellipse cx="{ox}" cy="{oy + s * 0.95:.1f}" rx="{s * 0.95:.1f}" ry="{s * 0.32:.1f}" fill="#0B1450" opacity="0.35" filter="url(#soft)"/>
    <g stroke="#FFFFFF" stroke-width="7" stroke-linejoin="round" stroke-opacity="0.9">
      <polygon points="{poly(left)}" fill="url(#left)"/>
      <polygon points="{poly(right)}" fill="url(#right)"/>
      <polygon points="{poly(top)}" fill="url(#top)"/>
    </g>
    <path d="{squircle}" fill="url(#sheen)"/>
  </g>
  <path d="{squircle}" fill="none" stroke="#FFFFFF" stroke-opacity="0.28" stroke-width="3"/>
</svg>
'''
open(sys.argv[1], "w").write(svg)
