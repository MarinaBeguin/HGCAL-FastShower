import geometry_cfg

# cm, cm, MeV
shower_moliere_radius = 2.8

# mean layer energy profile (MeV), taken from Full simulation (CMSSW_9_0_0_pre2 release) studies 
# generation at E = 35 GeV for  electrons, photons and E = 100 GeV for pions
shower_layers_energy = {11 : [1.5874, 3.3291, 6.1224, 10.6888, 14.4497, 20.3249, 22.7999, 28.3454,
                        31.4394, 40.9882, 36.8994, 37.8882, 31.1828, 30.3768, 23.5351, 22.3839,
                        16.3414, 15.1179, 12.3962, 12.1699, 7.4253, 5.9549, 3.7008, 2.9236, 1.6568,
                        1.4056, 1.2952, 0.8951, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0],
                        22 : [2.466, 7.143, 16.566, 34.336, 53.577, 85.543, 110.062, 149.944, 182.26,
                            260.408, 260.97, 281.75, 248.81, 253.78, 209.76, 202.41, 157.208, 148.61,
                            128.18, 126.56, 82.233, 67.392, 40.648, 31.169, 18.823, 16.165, 14.016,
                            3.811, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0],
                        211 : [0, 0.12722, 0.365879, 0.715952, 1.36913, 2.23068, 3.10895, 4.47463,
                            5.49343, 7.51191, 9.30754, 13.9761, 15.5622, 18.4595, 18.961, 22.3884,
                            22.2176, 25.3299, 24.697, 27.404, 31.1248, 40.6817, 39.7349, 43.6084,
                            42.6057, 44.953, 43.5433, 46.6512, 119.120, 158.841, 154.939, 164.025,
                            159.207, 150.806, 137.158, 127.758, 116.509, 106.758, 103.724, 92.581,
                            103.057, 32.0498, 25.2536, 22.2643, 18.4445, 16.002, 12.024, 10.165,
                            6.9689, 4.86094, 3.95406, 2.6002]
                       }

#evolution vs depth described by a parabolic function
#Parameters get from the Full simulation (CMSSW_9_0_0_pre2 release) with the TP studies as reference
# for electromagnetic shower
shower_transverse_parameters_electro = dict(a0=8.93, a1=0.046, a2=0.081)
shower_transverse_parameters_hadro = dict(a0=28, a1=0.3350, a2=0.052)

# coefficient core and halo for the transverse hadronic shower defines as :
# a_core * exp(r0_hadro/b_core) + a_halo * exp(r0_halo/b_halo)
a_core_hadro = 108.
b_core_hadro = 19.3
a_halo_hadro = 95.
b_halo_hadro = 76.

# energy resolution, determines nhitspergev if fluctuation is true
# [100, 200, 300] um
shower_alpha = {11 : [0.243, 0.214, 0.199],
                22 : [0.243, 0.214, 0.199],
                211 : [0.75, 0.75, 0.75]
                }


