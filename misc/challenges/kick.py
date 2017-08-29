import math
# ms^-2 = m / s^2
g = 9.81
# kg m^-3 = kg/m^3
air_density = 1.2

def cross_section(a):
  return math.pi*a**2

def F_g(m):
  return m*g

def F_d(drag_coeffcient, cross_section, velocity):
  return 0.5*drag_coeffcient*air_density*cross_section*velocity**2

# m
football_radius = 0.11
# kg
football_mass = 0.43

football_drag_coefficient = 0.4

#m/s
# 120 km/h = 33.33 m/s
V_hard = 33.33
# 30 km/h = 8.33 m/s
V_soft = 08.33

#Newton
F_d_hard = F_d(football_drag_coefficient, cross_section(football_radius), V_hard)
F_d_soft = F_d(football_drag_coefficient, cross_section(football_radius), V_soft)

#Newton
F_g = F_g(football_mass)

print "Hard kick drag: ", str(round(F_d_hard, 1)), "N"
print "Soft Kick drag: ", str(round(F_d_soft, 1)), "N"
print "gravitation force:", str(round(F_g, 1)), "N"

print "Hard kick ratio: ", F_d_hard/F_g
print "Soft kick ratio: ", F_d_soft/F_g
