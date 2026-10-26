// Dibuat otomatis oleh train_peringatan_dini.py - JANGAN diedit manual.
// Peluang udara MEMBURUK dalam 5 menit. Urutan fitur x[]:
//   0=debu, 1=gas, 2=suhu, 3=kelembapan, 4=sev, 5=debu_d1, 6=debu_d3, 7=debu_d5, 8=gas_d1, 9=gas_d3, 10=gas_d5, 11=debu_acc, 12=gas_acc, 13=suhu_d5, 14=lembap_d5, 15=debu_ke35, 16=gas_ke3, 17=debu_proj, 18=gas_proj
#pragma once

#define AI_HORIZON_MENIT 5
#define AI_AMBANG_DEFAULT 0.55f
#define AI_JUMLAH_FITUR 19
#define AI_JUMLAH_POHON 20

static inline void aiPohon0(const float* x, float* votes) {
  if (x[10] <= 0.6500f) {
    if (x[4] <= 0.5000f) {
      if (x[5] <= -5.1500f) {
        if (x[11] <= -6.2625f) {
          if (x[16] <= 0.1833f) {
            votes[0] += 1.0000f;
          } else {
            if (x[0] <= 8.0000f) {
              votes[0] += 1.0000f;
            } else {
              if (x[13] <= -0.3500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[0] <= 28.6500f) {
                  votes[0] += 0.1693f;
                  votes[1] += 0.8307f;
                } else {
                  votes[0] += 0.0214f;
                  votes[1] += 0.9786f;
                }
              }
            }
          }
        } else {
          if (x[15] <= 0.1357f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      } else {
        if (x[3] <= 81.0500f) {
          if (x[0] <= 28.8500f) {
            if (x[18] <= -0.2500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[3] <= 66.0500f) {
                if (x[9] <= -0.0500f) {
                  votes[0] += 0.7164f;
                  votes[1] += 0.2836f;
                } else {
                  votes[0] += 0.3945f;
                  votes[1] += 0.6055f;
                }
              } else {
                if (x[12] <= 0.5625f) {
                  votes[0] += 0.8876f;
                  votes[1] += 0.1124f;
                } else {
                  votes[0] += 0.2137f;
                  votes[1] += 0.7863f;
                }
              }
            }
          } else {
            if (x[13] <= -0.2500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[11] <= -0.0125f) {
                if (x[1] <= 1.7500f) {
                  votes[0] += 0.0249f;
                  votes[1] += 0.9751f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[3] <= 68.8500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0931f;
                  votes[1] += 0.9069f;
                }
              }
            }
          }
        } else {
          if (x[0] <= 27.9500f) {
            if (x[0] <= 11.5500f) {
              if (x[2] <= 21.1500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[2] <= 25.6500f) {
                  votes[0] += 0.4508f;
                  votes[1] += 0.5492f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[11] <= 3.2875f) {
                if (x[15] <= 0.3329f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[15] <= 0.7543f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2819f;
                  votes[1] += 0.7181f;
                }
              }
            }
          } else {
            if (x[2] <= 21.9500f) {
              if (x[6] <= -1.4500f) {
                if (x[9] <= -0.0500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1745f;
                  votes[1] += 0.8255f;
                }
              } else {
                if (x[2] <= 21.4500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[17] <= 1.3057f) {
                if (x[12] <= -0.3125f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1613f;
                  votes[1] += 0.8387f;
                }
              } else {
                if (x[16] <= 0.2167f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        }
      }
    } else {
      if (x[5] <= 8.4500f) {
        if (x[14] <= 3.3500f) {
          if (x[7] <= 1.6500f) {
            if (x[6] <= -49.0500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[11] <= 1.7500f) {
              if (x[17] <= 1.6486f) {
                if (x[14] <= -0.7500f) {
                  votes[0] += 0.5917f;
                  votes[1] += 0.4083f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 0.1534f;
                votes[1] += 0.8466f;
              }
            } else {
              votes[0] += 1.0000f;
            }
          }
        } else {
          if (x[15] <= 1.2014f) {
            votes[0] += 0.0387f;
            votes[1] += 0.9613f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      } else {
        if (x[14] <= -0.7000f) {
          votes[0] += 1.0000f;
        } else {
          if (x[18] <= 0.4167f) {
            votes[0] += 0.0502f;
            votes[1] += 0.9498f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      }
    }
  } else {
    if (x[14] <= -0.6500f) {
      votes[0] += 0.1078f;
      votes[1] += 0.8922f;
    } else {
      if (x[17] <= 1.8957f) {
        if (x[12] <= 0.0125f) {
          votes[0] += 0.1946f;
          votes[1] += 0.8054f;
        } else {
          votes[0] += 0.0086f;
          votes[1] += 0.9914f;
        }
      } else {
        votes[1] += 1.0000f;
      }
    }
  }
}

static inline void aiPohon1(const float* x, float* votes) {
  if (x[15] <= 0.8243f) {
    if (x[3] <= 66.1500f) {
      if (x[13] <= -0.3500f) {
        votes[0] += 1.0000f;
      } else {
        if (x[12] <= -0.0125f) {
          if (x[15] <= 0.3929f) {
            if (x[6] <= 0.5500f) {
              if (x[3] <= 65.9500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[6] <= -2.2000f) {
                  votes[0] += 0.1488f;
                  votes[1] += 0.8512f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[6] <= 1.2500f) {
                if (x[12] <= -0.0875f) {
                  votes[0] += 0.2078f;
                  votes[1] += 0.7922f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[7] <= -1.4500f) {
              if (x[0] <= 23.2000f) {
                if (x[6] <= -0.1000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0204f;
                  votes[1] += 0.9796f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[0] <= 13.9500f) {
                votes[0] += 0.1488f;
                votes[1] += 0.8512f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[11] <= 3.1625f) {
            if (x[1] <= 0.8500f) {
              if (x[5] <= 0.9500f) {
                if (x[3] <= 63.6500f) {
                  votes[0] += 0.6793f;
                  votes[1] += 0.3207f;
                } else {
                  votes[0] += 0.2950f;
                  votes[1] += 0.7050f;
                }
              } else {
                if (x[0] <= 19.0000f) {
                  votes[0] += 0.1444f;
                  votes[1] += 0.8556f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[2] <= 30.0500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[11] <= 7.0875f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 0.1695f;
              votes[1] += 0.8305f;
            }
          }
        }
      }
    } else {
      if (x[9] <= 0.4500f) {
        if (x[15] <= 0.1300f) {
          if (x[0] <= 2.6500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[14] <= 0.0500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[10] <= -0.0500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[6] <= -3.8500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0779f;
                  votes[1] += 0.9221f;
                }
              }
            }
          }
        } else {
          if (x[13] <= -0.0500f) {
            if (x[3] <= 95.0500f) {
              if (x[2] <= 25.2500f) {
                if (x[2] <= 25.1500f) {
                  votes[0] += 0.9453f;
                  votes[1] += 0.0547f;
                } else {
                  votes[0] += 0.2748f;
                  votes[1] += 0.7252f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[11] <= -1.4125f) {
                if (x[14] <= -0.0500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1044f;
                  votes[1] += 0.8956f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[6] <= -2.3500f) {
              if (x[18] <= 0.2833f) {
                if (x[3] <= 74.4500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2943f;
                  votes[1] += 0.7057f;
                }
              } else {
                if (x[16] <= 0.1167f) {
                  votes[0] += 0.2898f;
                  votes[1] += 0.7102f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[11] <= 1.2875f) {
                if (x[3] <= 87.5500f) {
                  votes[0] += 0.8797f;
                  votes[1] += 0.1203f;
                } else {
                  votes[0] += 0.5554f;
                  votes[1] += 0.4446f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        }
      } else {
        if (x[18] <= 1.0833f) {
          votes[0] += 1.0000f;
        } else {
          votes[0] += 0.0087f;
          votes[1] += 0.9913f;
        }
      }
    }
  } else {
    if (x[0] <= 34.9500f) {
      if (x[6] <= -0.8500f) {
        if (x[1] <= 1.8000f) {
          if (x[7] <= 3.6000f) {
            if (x[10] <= 0.2500f) {
              if (x[16] <= 0.1667f) {
                votes[0] += 1.0000f;
              } else {
                if (x[3] <= 79.7500f) {
                  votes[0] += 0.0150f;
                  votes[1] += 0.9850f;
                } else {
                  votes[0] += 0.0785f;
                  votes[1] += 0.9215f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[11] <= -3.3750f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      } else {
        if (x[10] <= -0.2500f) {
          votes[0] += 1.0000f;
        } else {
          if (x[16] <= 0.3833f) {
            if (x[0] <= 32.7500f) {
              if (x[7] <= -3.6500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[14] <= 1.5000f) {
                  votes[0] += 0.1826f;
                  votes[1] += 0.8174f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[14] <= -1.7500f) {
                votes[0] += 0.1272f;
                votes[1] += 0.8728f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[7] <= -0.8000f) {
              votes[0] += 0.0072f;
              votes[1] += 0.9928f;
            } else {
              if (x[17] <= 1.1271f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 0.0419f;
                votes[1] += 0.9581f;
              }
            }
          }
        }
      }
    } else {
      if (x[9] <= 0.9500f) {
        if (x[15] <= 1.4214f) {
          if (x[1] <= 1.0500f) {
            if (x[11] <= 10.2000f) {
              if (x[18] <= 0.6167f) {
                votes[0] += 1.0000f;
              } else {
                if (x[1] <= 0.9500f) {
                  votes[0] += 0.2428f;
                  votes[1] += 0.7572f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              votes[0] += 0.1695f;
              votes[1] += 0.8305f;
            }
          } else {
            if (x[5] <= -10.2500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          }
        } else {
          if (x[16] <= 0.6167f) {
            if (x[14] <= -0.2000f) {
              if (x[7] <= 2.5500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[15] <= 1.8543f) {
                  votes[0] += 0.0583f;
                  votes[1] += 0.9417f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[10] <= -5.3500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      } else {
        if (x[6] <= 15.7000f) {
          votes[0] += 0.0058f;
          votes[1] += 0.9942f;
        } else {
          votes[1] += 1.0000f;
        }
      }
    }
  }
}

static inline void aiPohon2(const float* x, float* votes) {
  if (x[7] <= 9.2500f) {
    if (x[3] <= 75.6500f) {
      if (x[7] <= 1.6500f) {
        if (x[2] <= 28.6500f) {
          if (x[18] <= -0.5833f) {
            if (x[6] <= 0.8500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 0.1294f;
              votes[1] += 0.8706f;
            }
          } else {
            if (x[9] <= 0.0500f) {
              if (x[6] <= -2.4500f) {
                if (x[5] <= -2.0500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.5709f;
                  votes[1] += 0.4291f;
                }
              } else {
                if (x[1] <= 0.6500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.7268f;
                  votes[1] += 0.2732f;
                }
              }
            } else {
              if (x[18] <= -0.2833f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[9] <= -0.0500f) {
            if (x[7] <= -1.5500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[7] <= -1.2500f) {
                if (x[13] <= -0.0500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1514f;
                  votes[1] += 0.8486f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[5] <= -5.8000f) {
              if (x[14] <= 0.5000f) {
                if (x[5] <= -7.4000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0194f;
                  votes[1] += 0.9806f;
                }
              } else {
                if (x[0] <= 18.7500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[0] <= 10.9500f) {
                if (x[14] <= -1.1500f) {
                  votes[0] += 0.5135f;
                  votes[1] += 0.4865f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[6] <= 0.8500f) {
                  votes[0] += 0.4171f;
                  votes[1] += 0.5829f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        }
      } else {
        if (x[0] <= 7.8500f) {
          if (x[1] <= 0.3500f) {
            if (x[16] <= 0.0833f) {
              if (x[6] <= 2.8000f) {
                if (x[2] <= 24.1500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 0.0561f;
                votes[1] += 0.9439f;
              }
            } else {
              if (x[6] <= 1.6000f) {
                votes[0] += 0.0098f;
                votes[1] += 0.9902f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[7] <= 2.6500f) {
            if (x[2] <= 29.0500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[2] <= 30.2500f) {
                if (x[0] <= 8.4500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1218f;
                  votes[1] += 0.8782f;
                }
              } else {
                if (x[1] <= 0.6500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.3223f;
                  votes[1] += 0.6777f;
                }
              }
            }
          } else {
            if (x[1] <= 1.1500f) {
              if (x[7] <= 6.9500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[1] <= 0.3500f) {
                  votes[0] += 0.2111f;
                  votes[1] += 0.7889f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[2] <= 25.6000f) {
                votes[0] += 0.0942f;
                votes[1] += 0.9058f;
              } else {
                if (x[8] <= 0.3500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1514f;
                  votes[1] += 0.8486f;
                }
              }
            }
          }
        }
      }
    } else {
      if (x[11] <= 0.5625f) {
        if (x[11] <= -5.9750f) {
          if (x[17] <= -0.6686f) {
            if (x[6] <= -6.4500f) {
              votes[0] += 0.1063f;
              votes[1] += 0.8937f;
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[1] <= 0.7500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[15] <= 1.0157f) {
                if (x[1] <= 0.9500f) {
                  votes[0] += 0.0918f;
                  votes[1] += 0.9082f;
                } else {
                  votes[0] += 0.0139f;
                  votes[1] += 0.9861f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[1] <= 0.6500f) {
            if (x[9] <= -0.0500f) {
              if (x[13] <= 0.0500f) {
                if (x[3] <= 89.6500f) {
                  votes[0] += 0.6072f;
                  votes[1] += 0.3928f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[6] <= 0.9000f) {
                  votes[0] += 0.1737f;
                  votes[1] += 0.8263f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[11] <= -2.1500f) {
                if (x[2] <= 25.2500f) {
                  votes[0] += 0.8340f;
                  votes[1] += 0.1660f;
                } else {
                  votes[0] += 0.1619f;
                  votes[1] += 0.8381f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[17] <= 0.4457f) {
              if (x[9] <= 0.0500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[11] <= -3.0125f) {
                  votes[0] += 0.2998f;
                  votes[1] += 0.7002f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[4] <= 0.5000f) {
                if (x[15] <= 0.7971f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0885f;
                  votes[1] += 0.9115f;
                }
              } else {
                if (x[15] <= 1.0100f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        }
      } else {
        if (x[16] <= 0.1500f) {
          votes[0] += 1.0000f;
        } else {
          if (x[15] <= 1.0443f) {
            if (x[16] <= 0.2833f) {
              if (x[7] <= -0.3500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[17] <= 0.5157f) {
                  votes[0] += 0.2629f;
                  votes[1] += 0.7371f;
                } else {
                  votes[0] += 0.6528f;
                  votes[1] += 0.3472f;
                }
              }
            } else {
              if (x[5] <= 1.9500f) {
                if (x[13] <= 0.3500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2111f;
                  votes[1] += 0.7889f;
                }
              } else {
                if (x[13] <= -0.3500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1534f;
                  votes[1] += 0.8466f;
                }
              }
            }
          } else {
            if (x[16] <= 0.2833f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      }
    }
  } else {
    if (x[8] <= 0.0500f) {
      votes[0] += 1.0000f;
    } else {
      if (x[9] <= 0.1500f) {
        votes[0] += 0.2292f;
        votes[1] += 0.7708f;
      } else {
        if (x[17] <= 1.8957f) {
          votes[0] += 0.0692f;
          votes[1] += 0.9308f;
        } else {
          if (x[18] <= 2.8167f) {
            votes[0] += 0.0289f;
            votes[1] += 0.9711f;
          } else {
            votes[1] += 1.0000f;
          }
        }
      }
    }
  }
}

static inline void aiPohon3(const float* x, float* votes) {
  if (x[18] <= 1.3833f) {
    if (x[11] <= -6.3125f) {
      if (x[4] <= 0.5000f) {
        if (x[2] <= 23.0500f) {
          votes[0] += 1.0000f;
        } else {
          if (x[10] <= -0.3500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[17] <= -0.6657f) {
              if (x[7] <= -2.0500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[13] <= -0.0500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0231f;
                  votes[1] += 0.9769f;
                }
              }
            } else {
              if (x[0] <= 24.4000f) {
                if (x[17] <= -0.5929f) {
                  votes[0] += 0.0953f;
                  votes[1] += 0.9047f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[7] <= 0.9500f) {
                  votes[0] += 0.0231f;
                  votes[1] += 0.9769f;
                } else {
                  votes[0] += 0.1811f;
                  votes[1] += 0.8189f;
                }
              }
            }
          }
        }
      } else {
        if (x[10] <= -0.0500f) {
          votes[0] += 1.0000f;
        } else {
          if (x[0] <= 37.3500f) {
            votes[0] += 0.0996f;
            votes[1] += 0.9004f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      }
    } else {
      if (x[4] <= 0.5000f) {
        if (x[0] <= 28.4500f) {
          if (x[3] <= 66.1500f) {
            if (x[16] <= 0.2500f) {
              if (x[2] <= 30.2500f) {
                if (x[14] <= -2.0500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2717f;
                  votes[1] += 0.7283f;
                }
              } else {
                if (x[6] <= 5.5000f) {
                  votes[0] += 0.7379f;
                  votes[1] += 0.2621f;
                } else {
                  votes[0] += 0.1916f;
                  votes[1] += 0.8084f;
                }
              }
            } else {
              if (x[2] <= 29.3500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[15] <= 0.1157f) {
              if (x[2] <= 22.2500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[15] <= 0.0443f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1927f;
                  votes[1] += 0.8073f;
                }
              }
            } else {
              if (x[6] <= -1.0500f) {
                if (x[15] <= 0.7614f) {
                  votes[0] += 0.7487f;
                  votes[1] += 0.2513f;
                } else {
                  votes[0] += 0.3191f;
                  votes[1] += 0.6809f;
                }
              } else {
                if (x[8] <= -0.3500f) {
                  votes[0] += 0.4244f;
                  votes[1] += 0.5756f;
                } else {
                  votes[0] += 0.9407f;
                  votes[1] += 0.0593f;
                }
              }
            }
          }
        } else {
          if (x[16] <= 0.5167f) {
            if (x[2] <= 23.4500f) {
              if (x[9] <= -0.0500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[18] <= 0.6500f) {
                  votes[0] += 0.3842f;
                  votes[1] += 0.6158f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[1] <= 0.6500f) {
                if (x[0] <= 29.0000f) {
                  votes[0] += 0.1122f;
                  votes[1] += 0.8878f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[5] <= 5.8000f) {
                  votes[0] += 0.1129f;
                  votes[1] += 0.8871f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[3] <= 63.7500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      } else {
        if (x[7] <= 1.1500f) {
          if (x[13] <= -0.8500f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[13] <= -0.0500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[5] <= 8.4500f) {
              if (x[15] <= 1.4114f) {
                if (x[3] <= 65.4500f) {
                  votes[0] += 0.6261f;
                  votes[1] += 0.3739f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[6] <= 1.1500f) {
                  votes[0] += 0.0452f;
                  votes[1] += 0.9548f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[12] <= 0.0625f) {
                if (x[18] <= 0.1500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1038f;
                  votes[1] += 0.8962f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        }
      }
    }
  } else {
    if (x[9] <= 0.4500f) {
      votes[0] += 1.0000f;
    } else {
      if (x[12] <= 0.0125f) {
        votes[0] += 0.0306f;
        votes[1] += 0.9694f;
      } else {
        if (x[17] <= 2.7057f) {
          if (x[16] <= 1.4667f) {
            votes[1] += 1.0000f;
          } else {
            votes[0] += 0.0125f;
            votes[1] += 0.9875f;
          }
        } else {
          if (x[9] <= 1.6500f) {
            votes[1] += 1.0000f;
          } else {
            votes[1] += 1.0000f;
          }
        }
      }
    }
  }
}

static inline void aiPohon4(const float* x, float* votes) {
  if (x[0] <= 27.9500f) {
    if (x[7] <= 8.1000f) {
      if (x[14] <= 2.7500f) {
        if (x[3] <= 65.3500f) {
          if (x[18] <= -0.2167f) {
            if (x[3] <= 63.4500f) {
              if (x[18] <= -0.2500f) {
                if (x[9] <= -0.3500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[0] <= 14.2000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1463f;
                  votes[1] += 0.8537f;
                }
              }
            } else {
              if (x[3] <= 64.5500f) {
                if (x[18] <= -0.4833f) {
                  votes[0] += 0.0345f;
                  votes[1] += 0.9655f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[11] <= 1.0000f) {
                  votes[0] += 0.1566f;
                  votes[1] += 0.8434f;
                } else {
                  votes[0] += 0.0141f;
                  votes[1] += 0.9859f;
                }
              }
            }
          } else {
            if (x[3] <= 62.6500f) {
              if (x[8] <= 0.0500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[13] <= 0.2500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2164f;
                  votes[1] += 0.7836f;
                }
              }
            } else {
              if (x[0] <= 10.9500f) {
                if (x[0] <= 3.9000f) {
                  votes[0] += 0.0909f;
                  votes[1] += 0.9091f;
                } else {
                  votes[0] += 0.8108f;
                  votes[1] += 0.1892f;
                }
              } else {
                if (x[0] <= 16.3500f) {
                  votes[0] += 0.2631f;
                  votes[1] += 0.7369f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        } else {
          if (x[3] <= 86.4500f) {
            if (x[16] <= 0.2833f) {
              if (x[18] <= -0.5833f) {
                if (x[0] <= 6.9000f) {
                  votes[0] += 0.1025f;
                  votes[1] += 0.8975f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[11] <= -7.3250f) {
                  votes[0] += 0.5569f;
                  votes[1] += 0.4431f;
                } else {
                  votes[0] += 0.9711f;
                  votes[1] += 0.0289f;
                }
              }
            } else {
              if (x[6] <= -3.6000f) {
                if (x[12] <= 0.0875f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1666f;
                  votes[1] += 0.8334f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[2] <= 21.5500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[5] <= -7.0500f) {
                votes[0] += 0.0489f;
                votes[1] += 0.9511f;
              } else {
                if (x[14] <= 0.2500f) {
                  votes[0] += 0.5129f;
                  votes[1] += 0.4871f;
                } else {
                  votes[0] += 0.9146f;
                  votes[1] += 0.0854f;
                }
              }
            }
          }
        }
      } else {
        if (x[0] <= 8.7500f) {
          if (x[16] <= 0.1167f) {
            if (x[13] <= 0.0500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[11] <= -0.9250f) {
                votes[0] += 0.0331f;
                votes[1] += 0.9669f;
              } else {
                votes[0] += 0.2391f;
                votes[1] += 0.7609f;
              }
            }
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[1] <= 0.8500f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 0.1666f;
            votes[1] += 0.8334f;
          }
        }
      }
    } else {
      if (x[15] <= 0.5800f) {
        votes[0] += 1.0000f;
      } else {
        votes[0] += 0.0200f;
        votes[1] += 0.9800f;
      }
    }
  } else {
    if (x[6] <= 8.8500f) {
      if (x[10] <= -0.3500f) {
        if (x[18] <= -0.1167f) {
          if (x[3] <= 79.6000f) {
            if (x[0] <= 40.4000f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            votes[0] += 0.1250f;
            votes[1] += 0.8750f;
          }
        } else {
          votes[0] += 1.0000f;
        }
      } else {
        if (x[15] <= 0.9986f) {
          if (x[11] <= 1.5125f) {
            if (x[13] <= -0.6500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[16] <= 0.2167f) {
                if (x[18] <= 0.1500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1463f;
                  votes[1] += 0.8537f;
                }
              } else {
                if (x[6] <= 4.0500f) {
                  votes[0] += 0.0820f;
                  votes[1] += 0.9180f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[13] <= -0.3500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[16] <= 0.2833f) {
                if (x[14] <= -2.0000f) {
                  votes[0] += 0.2391f;
                  votes[1] += 0.7609f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[12] <= 0.1625f) {
                  votes[0] += 0.1367f;
                  votes[1] += 0.8633f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        } else {
          if (x[13] <= -0.0500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[17] <= 1.6757f) {
              if (x[1] <= 1.4500f) {
                if (x[10] <= 0.1500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.7222f;
                  votes[1] += 0.2778f;
                }
              } else {
                if (x[3] <= 91.7000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1666f;
                  votes[1] += 0.8334f;
                }
              }
            } else {
              if (x[16] <= 0.3833f) {
                if (x[0] <= 36.9500f) {
                  votes[0] += 0.1666f;
                  votes[1] += 0.8334f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[11] <= 1.8250f) {
                  votes[0] += 0.0094f;
                  votes[1] += 0.9906f;
                } else {
                  votes[0] += 0.6391f;
                  votes[1] += 0.3609f;
                }
              }
            }
          }
        }
      }
    } else {
      if (x[8] <= 0.0500f) {
        votes[0] += 1.0000f;
      } else {
        if (x[7] <= 9.7000f) {
          votes[0] += 1.0000f;
        } else {
          if (x[10] <= 0.4500f) {
            votes[0] += 0.1666f;
            votes[1] += 0.8334f;
          } else {
            if (x[0] <= 55.6500f) {
              if (x[18] <= 3.2000f) {
                votes[0] += 0.2045f;
                votes[1] += 0.7955f;
              } else {
                votes[1] += 1.0000f;
              }
            } else {
              votes[1] += 1.0000f;
            }
          }
        }
      }
    }
  }
}

static inline void aiPohon5(const float* x, float* votes) {
  if (x[15] <= 0.8014f) {
    if (x[18] <= 1.4833f) {
      if (x[14] <= 2.7500f) {
        if (x[16] <= 0.1500f) {
          if (x[2] <= 29.6500f) {
            if (x[18] <= -0.5833f) {
              if (x[9] <= -0.0500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 0.1066f;
                votes[1] += 0.8934f;
              }
            } else {
              if (x[9] <= -0.4500f) {
                if (x[13] <= 0.0500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1298f;
                  votes[1] += 0.8702f;
                }
              } else {
                if (x[18] <= 0.0833f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.8949f;
                  votes[1] += 0.1051f;
                }
              }
            }
          } else {
            if (x[15] <= 0.1814f) {
              if (x[7] <= 1.5500f) {
                if (x[7] <= -4.7500f) {
                  votes[0] += 0.1298f;
                  votes[1] += 0.8702f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 0.0195f;
                votes[1] += 0.9805f;
              }
            } else {
              if (x[3] <= 64.2500f) {
                if (x[14] <= -2.1500f) {
                  votes[0] += 0.5677f;
                  votes[1] += 0.4323f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[9] <= 0.0500f) {
                  votes[0] += 0.3286f;
                  votes[1] += 0.6714f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        } else {
          if (x[10] <= 0.1500f) {
            if (x[3] <= 87.5500f) {
              if (x[2] <= 28.9500f) {
                if (x[7] <= -1.6500f) {
                  votes[0] += 0.7793f;
                  votes[1] += 0.2207f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[15] <= 0.4300f) {
                  votes[0] += 0.3594f;
                  votes[1] += 0.6406f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[7] <= -3.0500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[6] <= 1.6500f) {
                  votes[0] += 0.2493f;
                  votes[1] += 0.7507f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[5] <= -7.9000f) {
              votes[0] += 0.1519f;
              votes[1] += 0.8481f;
            } else {
              if (x[3] <= 64.3500f) {
                if (x[17] <= 0.3786f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.3853f;
                  votes[1] += 0.6147f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        }
      } else {
        if (x[15] <= 0.2514f) {
          if (x[1] <= 0.3500f) {
            if (x[14] <= 3.3500f) {
              if (x[11] <= -2.3500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[12] <= -0.0625f) {
                  votes[0] += 0.0694f;
                  votes[1] += 0.9306f;
                } else {
                  votes[0] += 0.0099f;
                  votes[1] += 0.9901f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          votes[0] += 1.0000f;
        }
      }
    } else {
      votes[1] += 1.0000f;
    }
  } else {
    if (x[9] <= 0.4500f) {
      if (x[0] <= 34.9500f) {
        if (x[1] <= 1.5500f) {
          if (x[2] <= 22.8500f) {
            if (x[13] <= 0.0500f) {
              if (x[6] <= 1.4500f) {
                if (x[0] <= 29.3500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0847f;
                  votes[1] += 0.9153f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[15] <= 0.8614f) {
                if (x[6] <= 1.9500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1066f;
                  votes[1] += 0.8934f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[6] <= 4.3500f) {
              if (x[5] <= 5.8000f) {
                if (x[16] <= 0.2167f) {
                  votes[0] += 0.5838f;
                  votes[1] += 0.4162f;
                } else {
                  votes[0] += 0.0827f;
                  votes[1] += 0.9173f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[16] <= 0.2500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          votes[0] += 1.0000f;
        }
      } else {
        if (x[16] <= 0.2167f) {
          if (x[17] <= 8.2614f) {
            if (x[9] <= -0.2500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            votes[0] += 0.0428f;
            votes[1] += 0.9572f;
          }
        } else {
          if (x[14] <= -0.7500f) {
            if (x[14] <= -0.8500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[16] <= 0.3167f) {
                votes[0] += 0.1066f;
                votes[1] += 0.8934f;
              } else {
                if (x[17] <= 1.1371f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            votes[0] += 1.0000f;
          }
        }
      }
    } else {
      if (x[8] <= 0.3500f) {
        votes[0] += 0.2637f;
        votes[1] += 0.7363f;
      } else {
        if (x[8] <= 0.5500f) {
          if (x[15] <= 1.2757f) {
            votes[0] += 0.0694f;
            votes[1] += 0.9306f;
          } else {
            votes[0] += 0.0290f;
            votes[1] += 0.9710f;
          }
        } else {
          votes[1] += 1.0000f;
        }
      }
    }
  }
}

static inline void aiPohon6(const float* x, float* votes) {
  if (x[6] <= 8.7500f) {
    if (x[15] <= 0.7443f) {
      if (x[6] <= 4.5500f) {
        if (x[16] <= 0.1500f) {
          if (x[6] <= -2.5500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[6] <= -2.0500f) {
              if (x[15] <= 0.1557f) {
                if (x[7] <= -1.7000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0212f;
                  votes[1] += 0.9788f;
                }
              } else {
                if (x[2] <= 23.9500f) {
                  votes[0] += 0.3295f;
                  votes[1] += 0.6705f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[2] <= 25.0500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[10] <= -0.0500f) {
                  votes[0] += 0.5768f;
                  votes[1] += 0.4232f;
                } else {
                  votes[0] += 0.8324f;
                  votes[1] += 0.1676f;
                }
              }
            }
          }
        } else {
          if (x[2] <= 28.9500f) {
            if (x[2] <= 21.6500f) {
              if (x[7] <= -0.4500f) {
                if (x[5] <= -2.5500f) {
                  votes[0] += 0.1548f;
                  votes[1] += 0.8452f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[12] <= -0.2125f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[18] <= 1.1500f) {
                if (x[14] <= -1.3500f) {
                  votes[0] += 0.7424f;
                  votes[1] += 0.2576f;
                } else {
                  votes[0] += 0.9537f;
                  votes[1] += 0.0463f;
                }
              } else {
                votes[0] += 0.1037f;
                votes[1] += 0.8963f;
              }
            }
          } else {
            if (x[7] <= -2.8500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[0] <= 15.0500f) {
                if (x[18] <= 0.5500f) {
                  votes[0] += 0.2520f;
                  votes[1] += 0.7480f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[11] <= 1.3000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.5268f;
                  votes[1] += 0.4732f;
                }
              }
            }
          }
        }
      } else {
        if (x[5] <= 2.4500f) {
          if (x[0] <= 15.5000f) {
            if (x[18] <= 0.0167f) {
              votes[0] += 1.0000f;
            } else {
              if (x[11] <= -1.0750f) {
                votes[0] += 1.0000f;
              } else {
                if (x[14] <= -0.0500f) {
                  votes[0] += 0.0306f;
                  votes[1] += 0.9694f;
                } else {
                  votes[0] += 0.3994f;
                  votes[1] += 0.6006f;
                }
              }
            }
          } else {
            if (x[1] <= 0.6000f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          }
        } else {
          if (x[10] <= -0.3500f) {
            votes[0] += 0.1263f;
            votes[1] += 0.8737f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      }
    } else {
      if (x[0] <= 36.7500f) {
        if (x[5] <= 4.1500f) {
          if (x[5] <= 0.3500f) {
            if (x[6] <= 3.2500f) {
              if (x[17] <= 0.9257f) {
                if (x[11] <= -6.2125f) {
                  votes[0] += 0.0366f;
                  votes[1] += 0.9634f;
                } else {
                  votes[0] += 0.1764f;
                  votes[1] += 0.8236f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[11] <= 1.3625f) {
              votes[0] += 1.0000f;
            } else {
              if (x[3] <= 82.4500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[13] <= -0.0500f) {
                  votes[0] += 0.5599f;
                  votes[1] += 0.4401f;
                } else {
                  votes[0] += 0.1571f;
                  votes[1] += 0.8429f;
                }
              }
            }
          }
        } else {
          votes[0] += 1.0000f;
        }
      } else {
        if (x[10] <= 0.7000f) {
          if (x[7] <= 2.5500f) {
            if (x[1] <= 0.2500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[7] <= 2.6500f) {
              votes[0] += 0.1478f;
              votes[1] += 0.8522f;
            } else {
              if (x[5] <= -4.0000f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          votes[0] += 0.0547f;
          votes[1] += 0.9453f;
        }
      }
    }
  } else {
    if (x[16] <= 0.1833f) {
      votes[0] += 1.0000f;
    } else {
      if (x[9] <= 0.0500f) {
        votes[0] += 1.0000f;
      } else {
        if (x[8] <= 0.3500f) {
          if (x[11] <= 9.0625f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 0.0371f;
            votes[1] += 0.9629f;
          }
        } else {
          if (x[5] <= 5.2000f) {
            votes[0] += 0.0095f;
            votes[1] += 0.9905f;
          } else {
            votes[1] += 1.0000f;
          }
        }
      }
    }
  }
}

static inline void aiPohon7(const float* x, float* votes) {
  if (x[16] <= 0.1833f) {
    if (x[10] <= 0.3500f) {
      if (x[7] <= 1.7500f) {
        if (x[16] <= 0.0833f) {
          if (x[15] <= 0.0471f) {
            if (x[12] <= -0.2125f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 0.1294f;
              votes[1] += 0.8706f;
            }
          } else {
            if (x[14] <= -1.4500f) {
              if (x[9] <= -0.0500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[10] <= -0.2500f) {
                  votes[0] += 0.1294f;
                  votes[1] += 0.8706f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[13] <= -0.6500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[0] <= 4.5500f) {
            if (x[12] <= 0.0875f) {
              if (x[8] <= -0.1500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[15] <= 0.0957f) {
                if (x[8] <= 0.1500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[2] <= 27.0500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0344f;
                  votes[1] += 0.9656f;
                }
              }
            }
          } else {
            if (x[2] <= 31.4500f) {
              if (x[18] <= 0.2167f) {
                if (x[10] <= -0.0500f) {
                  votes[0] += 0.6914f;
                  votes[1] += 0.3086f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[16] <= 0.1167f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[0] <= 14.4500f) {
                if (x[1] <= 0.4500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[11] <= 0.3000f) {
                  votes[0] += 0.0289f;
                  votes[1] += 0.9711f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        }
      } else {
        if (x[17] <= 0.1757f) {
          if (x[5] <= -1.4500f) {
            if (x[13] <= -0.2500f) {
              if (x[3] <= 67.5500f) {
                votes[0] += 0.0427f;
                votes[1] += 0.9573f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[6] <= -2.2500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[18] <= 0.1500f) {
              if (x[2] <= 25.0000f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 0.0182f;
                votes[1] += 0.9818f;
              }
            } else {
              votes[0] += 1.0000f;
            }
          }
        } else {
          if (x[6] <= 3.9500f) {
            if (x[7] <= 1.8500f) {
              if (x[2] <= 29.5500f) {
                if (x[8] <= -0.1500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 0.0819f;
                votes[1] += 0.9181f;
              }
            } else {
              if (x[17] <= 0.2614f) {
                if (x[7] <= 4.3500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2464f;
                  votes[1] += 0.7536f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[16] <= 0.1500f) {
              if (x[2] <= 29.9500f) {
                if (x[2] <= 20.3500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[0] <= 9.7500f) {
                  votes[0] += 0.1063f;
                  votes[1] += 0.8937f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[3] <= 88.9500f) {
                if (x[8] <= -0.1500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1331f;
                  votes[1] += 0.8669f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        }
      }
    } else {
      if (x[12] <= 0.0125f) {
        votes[0] += 0.0561f;
        votes[1] += 0.9439f;
      } else {
        if (x[3] <= 65.1000f) {
          votes[0] += 1.0000f;
        } else {
          votes[0] += 1.0000f;
        }
      }
    }
  } else {
    if (x[7] <= 8.1500f) {
      if (x[5] <= -0.4500f) {
        if (x[3] <= 75.6500f) {
          if (x[15] <= 0.9971f) {
            if (x[0] <= 31.8500f) {
              if (x[1] <= 0.7500f) {
                if (x[17] <= -0.5714f) {
                  votes[0] += 0.0756f;
                  votes[1] += 0.9244f;
                } else {
                  votes[0] += 0.7925f;
                  votes[1] += 0.2075f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[10] <= -0.5000f) {
                votes[0] += 1.0000f;
              } else {
                if (x[13] <= 0.1500f) {
                  votes[0] += 0.0118f;
                  votes[1] += 0.9882f;
                } else {
                  votes[0] += 0.0042f;
                  votes[1] += 0.9958f;
                }
              }
            }
          } else {
            if (x[17] <= 1.6357f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 0.1063f;
              votes[1] += 0.8937f;
            }
          }
        } else {
          if (x[0] <= 36.7500f) {
            if (x[15] <= 0.7843f) {
              if (x[12] <= -0.0625f) {
                if (x[7] <= -1.9500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1544f;
                  votes[1] += 0.8456f;
                }
              } else {
                if (x[6] <= 1.1500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.5369f;
                  votes[1] += 0.4631f;
                }
              }
            } else {
              if (x[4] <= 0.5000f) {
                if (x[2] <= 22.2500f) {
                  votes[0] += 0.4214f;
                  votes[1] += 0.5786f;
                } else {
                  votes[0] += 0.0682f;
                  votes[1] += 0.9318f;
                }
              } else {
                if (x[3] <= 90.1000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0692f;
                  votes[1] += 0.9308f;
                }
              }
            }
          } else {
            if (x[3] <= 76.0500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      } else {
        if (x[0] <= 36.5500f) {
          if (x[15] <= 0.7986f) {
            if (x[14] <= 0.8500f) {
              if (x[10] <= -0.0500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[18] <= 0.5833f) {
                  votes[0] += 0.4164f;
                  votes[1] += 0.5836f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[0] <= 6.3500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[9] <= -0.3500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[13] <= -0.4500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[16] <= 0.5167f) {
                  votes[0] += 0.2260f;
                  votes[1] += 0.7740f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        } else {
          if (x[0] <= 49.7000f) {
            votes[0] += 1.0000f;
          } else {
            if (x[13] <= 0.0500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[17] <= 1.7871f) {
                votes[0] += 0.0289f;
                votes[1] += 0.9711f;
              } else {
                if (x[13] <= 0.1500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        }
      }
    } else {
      if (x[9] <= 0.0500f) {
        if (x[6] <= 4.8500f) {
          votes[0] += 0.0819f;
          votes[1] += 0.9181f;
        } else {
          if (x[17] <= 2.0700f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      } else {
        if (x[18] <= 2.7000f) {
          if (x[5] <= 5.6500f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 0.0042f;
            votes[1] += 0.9958f;
          }
        } else {
          if (x[8] <= 1.1000f) {
            votes[0] += 0.0033f;
            votes[1] += 0.9967f;
          } else {
            if (x[2] <= 25.5500f) {
              votes[1] += 1.0000f;
            } else {
              votes[1] += 1.0000f;
            }
          }
        }
      }
    }
  }
}

static inline void aiPohon8(const float* x, float* votes) {
  if (x[1] <= 0.6500f) {
    if (x[1] <= 0.4500f) {
      if (x[6] <= 4.7500f) {
        if (x[6] <= 1.9500f) {
          if (x[7] <= 1.2500f) {
            if (x[2] <= 25.1500f) {
              if (x[1] <= 0.0500f) {
                if (x[6] <= 0.1000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1999f;
                  votes[1] += 0.8001f;
                }
              } else {
                if (x[6] <= -8.7000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[3] <= 69.2500f) {
                if (x[7] <= -4.2500f) {
                  votes[0] += 0.6287f;
                  votes[1] += 0.3713f;
                } else {
                  votes[0] += 0.9497f;
                  votes[1] += 0.0503f;
                }
              } else {
                if (x[0] <= 4.5500f) {
                  votes[0] += 0.1627f;
                  votes[1] += 0.8373f;
                } else {
                  votes[0] += 0.7516f;
                  votes[1] += 0.2484f;
                }
              }
            }
          } else {
            if (x[17] <= -0.1871f) {
              if (x[3] <= 69.1500f) {
                votes[0] += 0.0270f;
                votes[1] += 0.9730f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[10] <= -0.2500f) {
                if (x[5] <= -1.0000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2034f;
                  votes[1] += 0.7966f;
                }
              } else {
                if (x[17] <= 0.5443f) {
                  votes[0] += 0.7041f;
                  votes[1] += 0.2959f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        } else {
          if (x[6] <= 2.0500f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      } else {
        if (x[1] <= 0.1500f) {
          if (x[2] <= 27.6500f) {
            if (x[1] <= 0.0500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            votes[0] += 0.0226f;
            votes[1] += 0.9774f;
          }
        } else {
          votes[0] += 1.0000f;
        }
      }
    } else {
      if (x[3] <= 61.2500f) {
        if (x[10] <= 0.0500f) {
          votes[0] += 1.0000f;
        } else {
          if (x[0] <= 13.9500f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 0.0270f;
            votes[1] += 0.9730f;
          }
        }
      } else {
        if (x[11] <= 1.3875f) {
          if (x[10] <= 0.0500f) {
            if (x[12] <= -0.2125f) {
              votes[0] += 1.0000f;
            } else {
              if (x[2] <= 29.9500f) {
                if (x[9] <= 0.1500f) {
                  votes[0] += 0.2869f;
                  votes[1] += 0.7131f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[6] <= -4.8000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[6] <= 5.2500f) {
              if (x[14] <= 0.0500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[14] <= 0.3500f) {
                  votes[0] += 0.2550f;
                  votes[1] += 0.7450f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              votes[0] += 0.0649f;
              votes[1] += 0.9351f;
            }
          }
        } else {
          if (x[2] <= 29.2500f) {
            if (x[0] <= 4.0500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[11] <= 5.6125f) {
              if (x[17] <= 0.6414f) {
                if (x[9] <= 0.0500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1427f;
                  votes[1] += 0.8573f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              votes[0] += 0.0769f;
              votes[1] += 0.9231f;
            }
          }
        }
      }
    }
  } else {
    if (x[9] <= 0.5500f) {
      if (x[4] <= 0.5000f) {
        if (x[15] <= 0.7814f) {
          if (x[0] <= 17.6500f) {
            if (x[5] <= -3.0500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[3] <= 95.7000f) {
                if (x[12] <= -0.0125f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.5021f;
                  votes[1] += 0.4979f;
                }
              } else {
                if (x[6] <= -2.7000f) {
                  votes[0] += 0.0137f;
                  votes[1] += 0.9863f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[18] <= 0.4500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[18] <= 0.4833f) {
                if (x[0] <= 26.4500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0608f;
                  votes[1] += 0.9392f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[10] <= -0.3500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[11] <= 6.1625f) {
              if (x[0] <= 31.2500f) {
                if (x[2] <= 22.8500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1842f;
                  votes[1] += 0.8158f;
                }
              } else {
                if (x[3] <= 94.0500f) {
                  votes[0] += 0.0747f;
                  votes[1] += 0.9253f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[2] <= 22.0000f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        }
      } else {
        if (x[2] <= 23.9500f) {
          if (x[17] <= 0.3714f) {
            votes[0] += 0.0335f;
            votes[1] += 0.9665f;
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[15] <= 1.4214f) {
            votes[0] += 1.0000f;
          } else {
            if (x[15] <= 1.4614f) {
              if (x[12] <= 0.0375f) {
                if (x[17] <= 1.7886f) {
                  votes[0] += 0.0357f;
                  votes[1] += 0.9643f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      }
    } else {
      if (x[14] <= -0.6500f) {
        votes[0] += 0.0425f;
        votes[1] += 0.9575f;
      } else {
        if (x[8] <= 0.8500f) {
          if (x[0] <= 54.7000f) {
            votes[0] += 0.1627f;
            votes[1] += 0.8373f;
          } else {
            votes[1] += 1.0000f;
          }
        } else {
          if (x[5] <= 4.9500f) {
            votes[1] += 1.0000f;
          } else {
            votes[1] += 1.0000f;
          }
        }
      }
    }
  }
}

static inline void aiPohon9(const float* x, float* votes) {
  if (x[7] <= 8.1500f) {
    if (x[11] <= 0.5875f) {
      if (x[15] <= 0.7843f) {
        if (x[12] <= -0.2875f) {
          if (x[2] <= 29.9500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[0] <= 11.5500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[6] <= 1.3000f) {
                if (x[18] <= -0.2833f) {
                  votes[0] += 0.0805f;
                  votes[1] += 0.9195f;
                } else {
                  votes[0] += 0.0256f;
                  votes[1] += 0.9744f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[16] <= 0.0833f) {
            votes[0] += 1.0000f;
          } else {
            if (x[15] <= 0.2500f) {
              if (x[16] <= 0.2167f) {
                if (x[7] <= 2.0500f) {
                  votes[0] += 0.7755f;
                  votes[1] += 0.2245f;
                } else {
                  votes[0] += 0.2218f;
                  votes[1] += 0.7782f;
                }
              } else {
                if (x[11] <= -1.4000f) {
                  votes[0] += 0.1361f;
                  votes[1] += 0.8639f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[2] <= 23.8500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[3] <= 78.1500f) {
                  votes[0] += 0.8395f;
                  votes[1] += 0.1605f;
                } else {
                  votes[0] += 0.4832f;
                  votes[1] += 0.5168f;
                }
              }
            }
          }
        }
      } else {
        if (x[0] <= 36.7500f) {
          if (x[9] <= -0.2500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[6] <= 4.0500f) {
              if (x[7] <= -11.3500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[11] <= 0.1375f) {
                  votes[0] += 0.0958f;
                  votes[1] += 0.9042f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[17] <= 0.5600f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[13] <= -0.6500f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      }
    } else {
      if (x[16] <= 0.2167f) {
        if (x[2] <= 29.6500f) {
          if (x[6] <= 0.5500f) {
            if (x[11] <= 1.8125f) {
              if (x[2] <= 25.0500f) {
                if (x[16] <= 0.0500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[7] <= -0.5500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2925f;
                  votes[1] += 0.7075f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[12] <= -0.4875f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          }
        } else {
          if (x[5] <= 1.9500f) {
            if (x[0] <= 21.0000f) {
              votes[0] += 1.0000f;
            } else {
              if (x[0] <= 39.0000f) {
                votes[0] += 0.1361f;
                votes[1] += 0.8639f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[17] <= 0.9600f) {
              if (x[11] <= 4.0250f) {
                if (x[18] <= 0.0500f) {
                  votes[0] += 0.1416f;
                  votes[1] += 0.8584f;
                } else {
                  votes[0] += 0.4322f;
                  votes[1] += 0.5678f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      } else {
        if (x[15] <= 0.9900f) {
          if (x[0] <= 28.8500f) {
            if (x[10] <= 0.0500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[17] <= 0.6614f) {
                votes[0] += 1.0000f;
              } else {
                if (x[12] <= 0.1250f) {
                  votes[0] += 0.2470f;
                  votes[1] += 0.7530f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[12] <= 0.1375f) {
              if (x[7] <= 0.5500f) {
                if (x[2] <= 22.7500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.3085f;
                  votes[1] += 0.6915f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[2] <= 22.7500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[10] <= -0.1500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1004f;
                  votes[1] += 0.8996f;
                }
              }
            }
          }
        } else {
          if (x[0] <= 49.7000f) {
            votes[0] += 1.0000f;
          } else {
            if (x[9] <= -0.0500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[16] <= 1.8000f) {
                if (x[8] <= 0.0500f) {
                  votes[0] += 0.0499f;
                  votes[1] += 0.9501f;
                } else {
                  votes[0] += 0.2395f;
                  votes[1] += 0.7605f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        }
      }
    }
  } else {
    if (x[1] <= 1.8500f) {
      if (x[18] <= 0.3833f) {
        if (x[16] <= 0.2500f) {
          if (x[3] <= 84.6000f) {
            if (x[15] <= 0.7329f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 0.0206f;
              votes[1] += 0.9794f;
            }
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          votes[0] += 1.0000f;
        }
      } else {
        votes[0] += 1.0000f;
      }
    } else {
      if (x[18] <= 2.5167f) {
        votes[0] += 0.0338f;
        votes[1] += 0.9662f;
      } else {
        if (x[9] <= 1.6500f) {
          votes[0] += 0.0033f;
          votes[1] += 0.9967f;
        } else {
          votes[1] += 1.0000f;
        }
      }
    }
  }
}

static inline void aiPohon10(const float* x, float* votes) {
  if (x[0] <= 28.4500f) {
    if (x[8] <= 0.6500f) {
      if (x[2] <= 29.2500f) {
        if (x[6] <= -2.0500f) {
          if (x[11] <= -8.7500f) {
            if (x[18] <= 0.4000f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 0.0258f;
              votes[1] += 0.9742f;
            }
          } else {
            if (x[3] <= 95.6000f) {
              if (x[14] <= 2.2500f) {
                if (x[2] <= 27.1500f) {
                  votes[0] += 0.9604f;
                  votes[1] += 0.0396f;
                } else {
                  votes[0] += 0.6412f;
                  votes[1] += 0.3588f;
                }
              } else {
                if (x[16] <= 0.1167f) {
                  votes[0] += 0.1924f;
                  votes[1] += 0.8076f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[2] <= 21.4500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[16] <= 0.1500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0621f;
                  votes[1] += 0.9379f;
                }
              }
            }
          }
        } else {
          if (x[17] <= -0.3071f) {
            if (x[5] <= -2.9500f) {
              if (x[13] <= 0.2500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[14] <= 1.1000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1169f;
                  votes[1] += 0.8831f;
                }
              }
            } else {
              votes[0] += 0.0258f;
              votes[1] += 0.9742f;
            }
          } else {
            if (x[3] <= 78.6500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[14] <= -2.6500f) {
                if (x[8] <= -0.0500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1436f;
                  votes[1] += 0.8564f;
                }
              } else {
                if (x[9] <= -0.0500f) {
                  votes[0] += 0.6271f;
                  votes[1] += 0.3729f;
                } else {
                  votes[0] += 0.8704f;
                  votes[1] += 0.1296f;
                }
              }
            }
          }
        }
      } else {
        if (x[11] <= 1.3375f) {
          if (x[11] <= -0.9875f) {
            if (x[6] <= -3.8500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[6] <= 3.8000f) {
                if (x[0] <= 6.3500f) {
                  votes[0] += 0.1855f;
                  votes[1] += 0.8145f;
                } else {
                  votes[0] += 0.6578f;
                  votes[1] += 0.3422f;
                }
              } else {
                votes[0] += 0.0503f;
                votes[1] += 0.9497f;
              }
            }
          } else {
            if (x[10] <= -0.0500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[17] <= 0.3557f) {
                votes[0] += 1.0000f;
              } else {
                if (x[11] <= 0.5875f) {
                  votes[0] += 0.3537f;
                  votes[1] += 0.6463f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        } else {
          if (x[3] <= 64.5500f) {
            if (x[9] <= 0.0500f) {
              if (x[3] <= 60.0000f) {
                votes[0] += 0.1564f;
                votes[1] += 0.8436f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[1] <= 0.5500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[5] <= 2.2500f) {
                  votes[0] += 0.0463f;
                  votes[1] += 0.9537f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[13] <= 0.2500f) {
              if (x[1] <= 0.7500f) {
                if (x[7] <= 2.3500f) {
                  votes[0] += 0.3983f;
                  votes[1] += 0.6017f;
                } else {
                  votes[0] += 0.0481f;
                  votes[1] += 0.9519f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      }
    } else {
      votes[0] += 0.0022f;
      votes[1] += 0.9978f;
    }
  } else {
    if (x[7] <= 14.5000f) {
      if (x[17] <= 0.9157f) {
        if (x[10] <= -0.5500f) {
          votes[0] += 1.0000f;
        } else {
          if (x[15] <= 0.9971f) {
            if (x[16] <= 0.1833f) {
              votes[0] += 1.0000f;
            } else {
              if (x[0] <= 31.4500f) {
                if (x[1] <= 0.6500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1002f;
                  votes[1] += 0.8998f;
                }
              } else {
                if (x[2] <= 22.5500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0307f;
                  votes[1] += 0.9693f;
                }
              }
            }
          } else {
            if (x[1] <= 1.4500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[14] <= 1.7000f) {
                if (x[14] <= -1.6000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 0.1169f;
                votes[1] += 0.8831f;
              }
            }
          }
        }
      } else {
        if (x[6] <= 4.3500f) {
          if (x[5] <= 1.2500f) {
            if (x[15] <= 2.6171f) {
              if (x[8] <= 0.1500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[6] <= 2.8500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1169f;
                  votes[1] += 0.8831f;
                }
              }
            } else {
              votes[0] += 0.0503f;
              votes[1] += 0.9497f;
            }
          } else {
            if (x[4] <= 0.5000f) {
              if (x[10] <= -0.2500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[13] <= -0.4500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1961f;
                  votes[1] += 0.8039f;
                }
              }
            } else {
              if (x[15] <= 1.4529f) {
                votes[0] += 1.0000f;
              } else {
                if (x[11] <= 2.9875f) {
                  votes[0] += 0.0736f;
                  votes[1] += 0.9264f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        } else {
          votes[0] += 1.0000f;
        }
      }
    } else {
      if (x[9] <= 0.4000f) {
        votes[0] += 1.0000f;
      } else {
        if (x[18] <= 2.8500f) {
          if (x[1] <= 3.0500f) {
            votes[1] += 1.0000f;
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[10] <= 3.1500f) {
            votes[1] += 1.0000f;
          } else {
            votes[1] += 1.0000f;
          }
        }
      }
    }
  }
}

static inline void aiPohon11(const float* x, float* votes) {
  if (x[0] <= 24.3500f) {
    if (x[2] <= 29.2500f) {
      if (x[17] <= 0.3386f) {
        if (x[11] <= -3.1375f) {
          if (x[5] <= -5.8500f) {
            if (x[17] <= -0.5986f) {
              if (x[5] <= -40.1500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[3] <= 72.7500f) {
                votes[0] += 0.1483f;
                votes[1] += 0.8517f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[13] <= 0.0500f) {
            if (x[18] <= 0.1167f) {
              votes[0] += 1.0000f;
            } else {
              if (x[17] <= -0.2414f) {
                if (x[0] <= 3.8500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0350f;
                  votes[1] += 0.9650f;
                }
              } else {
                if (x[8] <= 0.0500f) {
                  votes[0] += 0.4855f;
                  votes[1] += 0.5145f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[3] <= 70.6500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[9] <= -0.0500f) {
                if (x[6] <= -2.4500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1875f;
                  votes[1] += 0.8125f;
                }
              } else {
                if (x[12] <= 0.0875f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.4238f;
                  votes[1] += 0.5762f;
                }
              }
            }
          }
        }
      } else {
        if (x[9] <= 0.4500f) {
          if (x[18] <= 0.1500f) {
            if (x[3] <= 65.3500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[17] <= 0.4757f) {
              if (x[17] <= 0.4214f) {
                votes[0] += 1.0000f;
              } else {
                if (x[5] <= 1.2500f) {
                  votes[0] += 0.3712f;
                  votes[1] += 0.6288f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[10] <= -0.3500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[7] <= 2.4500f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 0.0213f;
            votes[1] += 0.9787f;
          }
        }
      }
    } else {
      if (x[7] <= 1.6500f) {
        if (x[11] <= 3.0875f) {
          if (x[1] <= 0.3500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[11] <= -2.3875f) {
              if (x[9] <= -0.0500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[18] <= 0.3500f) {
                  votes[0] += 0.2225f;
                  votes[1] += 0.7775f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[18] <= 0.1833f) {
                if (x[15] <= 0.3829f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.4967f;
                  votes[1] += 0.5033f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[17] <= 0.7943f) {
            if (x[6] <= 0.8000f) {
              if (x[0] <= 9.8000f) {
                votes[0] += 1.0000f;
              } else {
                if (x[7] <= -2.0500f) {
                  votes[0] += 0.0922f;
                  votes[1] += 0.9078f;
                } else {
                  votes[0] += 0.0171f;
                  votes[1] += 0.9829f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            votes[0] += 1.0000f;
          }
        }
      } else {
        if (x[1] <= 0.1500f) {
          if (x[2] <= 30.4500f) {
            if (x[9] <= -0.1500f) {
              votes[0] += 0.2250f;
              votes[1] += 0.7750f;
            } else {
              votes[0] += 0.0163f;
              votes[1] += 0.9837f;
            }
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[18] <= 0.3833f) {
            if (x[0] <= 11.0500f) {
              if (x[3] <= 62.9500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[1] <= 0.2500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1268f;
                  votes[1] += 0.8732f;
                }
              }
            } else {
              if (x[16] <= 0.2167f) {
                if (x[0] <= 11.2500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 0.3034f;
                votes[1] += 0.6966f;
              }
            }
          } else {
            if (x[14] <= -0.3500f) {
              if (x[18] <= 0.5500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 0.2420f;
                votes[1] += 0.7580f;
              }
            } else {
              if (x[10] <= -0.0500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[7] <= 2.7500f) {
                  votes[0] += 0.0203f;
                  votes[1] += 0.9797f;
                } else {
                  votes[0] += 0.2420f;
                  votes[1] += 0.7580f;
                }
              }
            }
          }
        }
      }
    }
  } else {
    if (x[8] <= 0.4500f) {
      if (x[4] <= 0.5000f) {
        if (x[0] <= 27.3500f) {
          if (x[5] <= -8.0000f) {
            votes[0] += 0.0719f;
            votes[1] += 0.9281f;
          } else {
            if (x[18] <= 0.4500f) {
              if (x[8] <= -0.2500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[13] <= 0.4500f) {
                if (x[1] <= 0.7500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 0.1040f;
                votes[1] += 0.8960f;
              }
            }
          }
        } else {
          if (x[5] <= -0.0500f) {
            if (x[14] <= 2.7500f) {
              if (x[0] <= 29.9500f) {
                if (x[0] <= 29.4500f) {
                  votes[0] += 0.1622f;
                  votes[1] += 0.8378f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[6] <= 4.0500f) {
                  votes[0] += 0.0530f;
                  votes[1] += 0.9470f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[12] <= 0.1375f) {
              if (x[10] <= -0.2500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[7] <= -0.0500f) {
                  votes[0] += 0.3034f;
                  votes[1] += 0.6966f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[10] <= -0.1500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[3] <= 87.0500f) {
                  votes[0] += 0.0911f;
                  votes[1] += 0.9089f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        }
      } else {
        if (x[14] <= 3.3500f) {
          if (x[11] <= 10.2625f) {
            if (x[6] <= 8.8500f) {
              if (x[3] <= 65.4500f) {
                if (x[17] <= 1.2671f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.7369f;
                  votes[1] += 0.2631f;
                }
              } else {
                if (x[16] <= 0.0833f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[7] <= 18.5000f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 0.1483f;
                votes[1] += 0.8517f;
              }
            }
          } else {
            if (x[7] <= 0.6500f) {
              if (x[11] <= 10.7625f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[13] <= 0.2500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 0.0483f;
                votes[1] += 0.9517f;
              }
            }
          }
        } else {
          if (x[15] <= 1.0729f) {
            votes[0] += 0.0549f;
            votes[1] += 0.9451f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      }
    } else {
      if (x[3] <= 65.3500f) {
        votes[0] += 1.0000f;
      } else {
        if (x[16] <= 0.7167f) {
          votes[0] += 0.0282f;
          votes[1] += 0.9718f;
        } else {
          votes[1] += 1.0000f;
        }
      }
    }
  }
}

static inline void aiPohon12(const float* x, float* votes) {
  if (x[0] <= 28.0500f) {
    if (x[5] <= -7.0500f) {
      if (x[18] <= 0.1167f) {
        votes[0] += 1.0000f;
      } else {
        if (x[6] <= -5.8000f) {
          votes[0] += 1.0000f;
        } else {
          if (x[18] <= 0.2500f) {
            votes[0] += 0.0049f;
            votes[1] += 0.9951f;
          } else {
            if (x[12] <= 0.1500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 0.0694f;
              votes[1] += 0.9306f;
            }
          }
        }
      }
    } else {
      if (x[6] <= 6.7500f) {
        if (x[9] <= -0.0500f) {
          if (x[5] <= -1.2500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[10] <= -0.1500f) {
              if (x[17] <= 0.2614f) {
                if (x[2] <= 26.2500f) {
                  votes[0] += 0.4724f;
                  votes[1] += 0.5276f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[17] <= 0.1986f) {
                if (x[16] <= 0.0833f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2853f;
                  votes[1] += 0.7147f;
                }
              } else {
                if (x[12] <= -0.2375f) {
                  votes[0] += 0.6035f;
                  votes[1] += 0.3965f;
                } else {
                  votes[0] += 0.8335f;
                  votes[1] += 0.1665f;
                }
              }
            }
          }
        } else {
          if (x[3] <= 66.1500f) {
            if (x[18] <= 0.0500f) {
              if (x[15] <= 0.2443f) {
                votes[0] += 1.0000f;
              } else {
                if (x[3] <= 64.2500f) {
                  votes[0] += 0.3963f;
                  votes[1] += 0.6037f;
                } else {
                  votes[0] += 0.1043f;
                  votes[1] += 0.8957f;
                }
              }
            } else {
              if (x[3] <= 59.6000f) {
                votes[0] += 0.0651f;
                votes[1] += 0.9349f;
              } else {
                if (x[13] <= -0.2500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.6063f;
                  votes[1] += 0.3937f;
                }
              }
            }
          } else {
            if (x[18] <= 0.1167f) {
              if (x[17] <= 0.1043f) {
                if (x[6] <= 1.8500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1728f;
                  votes[1] += 0.8272f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[11] <= -1.4125f) {
                if (x[12] <= 0.0625f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.4209f;
                  votes[1] += 0.5791f;
                }
              } else {
                if (x[18] <= 1.0833f) {
                  votes[0] += 0.8899f;
                  votes[1] += 0.1101f;
                } else {
                  votes[0] += 0.2298f;
                  votes[1] += 0.7702f;
                }
              }
            }
          }
        }
      } else {
        if (x[18] <= 0.5500f) {
          votes[0] += 1.0000f;
        } else {
          votes[0] += 0.0066f;
          votes[1] += 0.9934f;
        }
      }
    }
  } else {
    if (x[8] <= 0.4500f) {
      if (x[9] <= -0.3500f) {
        votes[0] += 1.0000f;
      } else {
        if (x[11] <= 1.6875f) {
          if (x[3] <= 75.2500f) {
            if (x[11] <= 0.4250f) {
              if (x[4] <= 0.5000f) {
                if (x[11] <= -2.5750f) {
                  votes[0] += 0.0290f;
                  votes[1] += 0.9710f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[6] <= 0.1000f) {
                if (x[3] <= 63.9500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0720f;
                  votes[1] += 0.9280f;
                }
              } else {
                if (x[5] <= 0.7500f) {
                  votes[0] += 0.1927f;
                  votes[1] += 0.8073f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[15] <= 1.0500f) {
              if (x[7] <= 5.1500f) {
                if (x[6] <= 4.0500f) {
                  votes[0] += 0.1017f;
                  votes[1] += 0.8983f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[18] <= 0.0833f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[16] <= 0.2500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[2] <= 27.7500f) {
            if (x[3] <= 93.9500f) {
              if (x[0] <= 33.7500f) {
                if (x[3] <= 85.7500f) {
                  votes[0] += 0.1066f;
                  votes[1] += 0.8934f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[3] <= 95.4500f) {
                votes[0] += 0.0147f;
                votes[1] += 0.9853f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[0] <= 73.3500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 0.1066f;
              votes[1] += 0.8934f;
            }
          }
        }
      }
    } else {
      if (x[17] <= 1.7043f) {
        votes[0] += 1.0000f;
      } else {
        if (x[10] <= 1.0000f) {
          votes[0] += 0.0290f;
          votes[1] += 0.9710f;
        } else {
          votes[1] += 1.0000f;
        }
      }
    }
  }
}

static inline void aiPohon13(const float* x, float* votes) {
  if (x[6] <= 8.7500f) {
    if (x[1] <= 0.6500f) {
      if (x[12] <= 0.2875f) {
        if (x[6] <= 5.2500f) {
          if (x[7] <= -5.0500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[3] <= 64.7500f) {
              if (x[3] <= 64.1500f) {
                if (x[2] <= 31.4500f) {
                  votes[0] += 0.7875f;
                  votes[1] += 0.2125f;
                } else {
                  votes[0] += 0.2525f;
                  votes[1] += 0.7475f;
                }
              } else {
                if (x[6] <= -3.2500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1849f;
                  votes[1] += 0.8151f;
                }
              }
            } else {
              if (x[5] <= 1.2500f) {
                if (x[0] <= 4.5500f) {
                  votes[0] += 0.4206f;
                  votes[1] += 0.5794f;
                } else {
                  votes[0] += 0.7600f;
                  votes[1] += 0.2400f;
                }
              } else {
                if (x[3] <= 66.0500f) {
                  votes[0] += 0.6479f;
                  votes[1] += 0.3521f;
                } else {
                  votes[0] += 0.9670f;
                  votes[1] += 0.0330f;
                }
              }
            }
          }
        } else {
          if (x[15] <= 0.3100f) {
            if (x[6] <= 5.6500f) {
              if (x[14] <= 0.5500f) {
                votes[0] += 0.0388f;
                votes[1] += 0.9612f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            votes[0] += 1.0000f;
          }
        }
      } else {
        votes[0] += 1.0000f;
      }
    } else {
      if (x[4] <= 0.5000f) {
        if (x[0] <= 27.9500f) {
          if (x[12] <= 0.2625f) {
            if (x[14] <= 0.3500f) {
              if (x[0] <= 17.6500f) {
                if (x[10] <= -0.0500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2449f;
                  votes[1] += 0.7551f;
                }
              } else {
                if (x[13] <= 0.5500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1500f;
                  votes[1] += 0.8500f;
                }
              }
            } else {
              if (x[11] <= -8.4500f) {
                votes[0] += 0.0364f;
                votes[1] += 0.9636f;
              } else {
                if (x[17] <= 1.0786f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.4387f;
                  votes[1] += 0.5613f;
                }
              }
            }
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[11] <= 5.5875f) {
            if (x[1] <= 1.7500f) {
              if (x[2] <= 22.8500f) {
                if (x[17] <= 0.8286f) {
                  votes[0] += 0.2539f;
                  votes[1] += 0.7461f;
                } else {
                  votes[0] += 0.7180f;
                  votes[1] += 0.2820f;
                }
              } else {
                if (x[6] <= 4.3500f) {
                  votes[0] += 0.1015f;
                  votes[1] += 0.8985f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[12] <= -0.1875f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[14] <= -1.0500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      } else {
        if (x[1] <= 6.2500f) {
          if (x[10] <= 0.5500f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 0.1119f;
            votes[1] += 0.8881f;
          }
        } else {
          if (x[9] <= 0.1500f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 0.0364f;
            votes[1] += 0.9636f;
          }
        }
      }
    }
  } else {
    if (x[18] <= 0.3167f) {
      votes[0] += 1.0000f;
    } else {
      if (x[10] <= 0.5000f) {
        if (x[18] <= 0.3833f) {
          votes[0] += 0.0149f;
          votes[1] += 0.9851f;
        } else {
          votes[0] += 1.0000f;
        }
      } else {
        if (x[5] <= 5.4000f) {
          votes[0] += 0.0111f;
          votes[1] += 0.9889f;
        } else {
          if (x[5] <= 9.5000f) {
            votes[0] += 0.0023f;
            votes[1] += 0.9977f;
          } else {
            votes[1] += 1.0000f;
          }
        }
      }
    }
  }
}

static inline void aiPohon14(const float* x, float* votes) {
  if (x[18] <= 0.9167f) {
    if (x[16] <= 0.1500f) {
      if (x[9] <= -0.0500f) {
        if (x[0] <= 1.8500f) {
          votes[0] += 0.1069f;
          votes[1] += 0.8931f;
        } else {
          if (x[14] <= 1.2500f) {
            if (x[16] <= 0.0167f) {
              if (x[9] <= -0.1500f) {
                if (x[9] <= -0.3500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[0] <= 6.2500f) {
                  votes[0] += 0.1754f;
                  votes[1] += 0.8246f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[3] <= 78.5500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[15] <= 0.3186f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.6908f;
                  votes[1] += 0.3092f;
                }
              }
            }
          } else {
            if (x[10] <= 0.1500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[3] <= 64.7500f) {
                votes[0] += 0.0424f;
                votes[1] += 0.9576f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        }
      } else {
        if (x[2] <= 25.0500f) {
          if (x[18] <= 0.4167f) {
            votes[0] += 1.0000f;
          } else {
            if (x[6] <= -6.4500f) {
              votes[0] += 0.1376f;
              votes[1] += 0.8624f;
            } else {
              if (x[12] <= 0.1875f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[18] <= -0.5167f) {
            votes[0] += 0.0259f;
            votes[1] += 0.9741f;
          } else {
            if (x[10] <= -0.2500f) {
              if (x[7] <= 1.2000f) {
                if (x[8] <= -0.2500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[7] <= 2.4500f) {
                  votes[0] += 0.1174f;
                  votes[1] += 0.8826f;
                } else {
                  votes[0] += 0.0196f;
                  votes[1] += 0.9804f;
                }
              }
            } else {
              if (x[2] <= 29.8500f) {
                if (x[11] <= -1.8500f) {
                  votes[0] += 0.6495f;
                  votes[1] += 0.3505f;
                } else {
                  votes[0] += 0.9216f;
                  votes[1] += 0.0784f;
                }
              } else {
                if (x[0] <= 6.4000f) {
                  votes[0] += 0.1139f;
                  votes[1] += 0.8861f;
                } else {
                  votes[0] += 0.6473f;
                  votes[1] += 0.3527f;
                }
              }
            }
          }
        }
      }
    } else {
      if (x[15] <= 0.9929f) {
        if (x[11] <= -5.9750f) {
          if (x[2] <= 22.9000f) {
            votes[0] += 1.0000f;
          } else {
            if (x[9] <= -0.2500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[15] <= 0.7414f) {
                if (x[17] <= -0.8743f) {
                  votes[0] += 0.0424f;
                  votes[1] += 0.9576f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[13] <= -0.1500f) {
                  votes[0] += 0.0584f;
                  votes[1] += 0.9416f;
                } else {
                  votes[0] += 0.0125f;
                  votes[1] += 0.9875f;
                }
              }
            }
          }
        } else {
          if (x[0] <= 28.0500f) {
            if (x[15] <= 0.5414f) {
              if (x[7] <= -0.5500f) {
                if (x[17] <= -0.1271f) {
                  votes[0] += 0.5516f;
                  votes[1] += 0.4484f;
                } else {
                  votes[0] += 0.8315f;
                  votes[1] += 0.1685f;
                }
              } else {
                if (x[3] <= 87.5500f) {
                  votes[0] += 0.6500f;
                  votes[1] += 0.3500f;
                } else {
                  votes[0] += 0.2746f;
                  votes[1] += 0.7254f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[16] <= 0.4833f) {
              if (x[6] <= -0.6500f) {
                if (x[12] <= 0.2875f) {
                  votes[0] += 0.0922f;
                  votes[1] += 0.9078f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[17] <= 0.7000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2845f;
                  votes[1] += 0.7155f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      } else {
        if (x[5] <= 43.5500f) {
          if (x[12] <= 0.1875f) {
            votes[0] += 1.0000f;
          } else {
            if (x[2] <= 29.7000f) {
              if (x[2] <= 22.9500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[12] <= 0.2125f) {
                votes[0] += 0.0662f;
                votes[1] += 0.9338f;
              } else {
                if (x[0] <= 38.8000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        } else {
          votes[0] += 0.0505f;
          votes[1] += 0.9495f;
        }
      }
    }
  } else {
    if (x[8] <= 0.2500f) {
      votes[0] += 1.0000f;
    } else {
      if (x[17] <= 0.6814f) {
        if (x[7] <= -6.7500f) {
          votes[0] += 0.0814f;
          votes[1] += 0.9186f;
        } else {
          if (x[16] <= 0.2167f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      } else {
        if (x[3] <= 63.9000f) {
          votes[0] += 1.0000f;
        } else {
          if (x[10] <= -0.0500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[17] <= 1.8614f) {
              if (x[14] <= -0.2500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[2] <= 24.4500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0553f;
                  votes[1] += 0.9447f;
                }
              }
            } else {
              if (x[8] <= 0.5500f) {
                votes[0] += 0.0088f;
                votes[1] += 0.9912f;
              } else {
                votes[1] += 1.0000f;
              }
            }
          }
        }
      }
    }
  }
}

static inline void aiPohon15(const float* x, float* votes) {
  if (x[1] <= 0.6500f) {
    if (x[1] <= 0.4500f) {
      if (x[2] <= 25.0500f) {
        if (x[18] <= 0.4167f) {
          if (x[10] <= -0.2500f) {
            if (x[12] <= 0.0375f) {
              votes[0] += 1.0000f;
            } else {
              if (x[3] <= 78.1500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[7] <= -1.1000f) {
                  votes[0] += 0.1604f;
                  votes[1] += 0.8396f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[6] <= -5.1500f) {
            votes[0] += 0.0757f;
            votes[1] += 0.9243f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      } else {
        if (x[0] <= 3.7500f) {
          if (x[15] <= 0.0943f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 0.0435f;
            votes[1] += 0.9565f;
          }
        } else {
          if (x[2] <= 25.6500f) {
            if (x[3] <= 77.1000f) {
              if (x[17] <= 0.6429f) {
                votes[0] += 1.0000f;
              } else {
                if (x[17] <= 0.6971f) {
                  votes[0] += 0.0984f;
                  votes[1] += 0.9016f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[17] <= 0.2657f) {
                if (x[18] <= -0.1500f) {
                  votes[0] += 0.1201f;
                  votes[1] += 0.8799f;
                } else {
                  votes[0] += 0.0161f;
                  votes[1] += 0.9839f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[12] <= -0.2875f) {
              if (x[14] <= 1.4500f) {
                if (x[12] <= -0.4375f) {
                  votes[0] += 0.4885f;
                  votes[1] += 0.5115f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[14] <= 2.3000f) {
                  votes[0] += 0.0476f;
                  votes[1] += 0.9524f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[14] <= -1.1500f) {
                if (x[1] <= 0.3500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.4375f;
                  votes[1] += 0.5625f;
                }
              } else {
                if (x[11] <= -4.3875f) {
                  votes[0] += 0.7012f;
                  votes[1] += 0.2988f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        }
      }
    } else {
      if (x[15] <= 0.8243f) {
        if (x[3] <= 94.4500f) {
          if (x[3] <= 66.0500f) {
            if (x[15] <= 0.4314f) {
              if (x[15] <= 0.3929f) {
                if (x[3] <= 63.5500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.3473f;
                  votes[1] += 0.6527f;
                }
              } else {
                if (x[7] <= 2.7000f) {
                  votes[0] += 0.0984f;
                  votes[1] += 0.9016f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[8] <= 0.0500f) {
              if (x[12] <= -0.0125f) {
                if (x[8] <= -0.1500f) {
                  votes[0] += 0.8235f;
                  votes[1] += 0.1765f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[3] <= 86.4500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2950f;
                  votes[1] += 0.7050f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          }
        } else {
          if (x[13] <= 0.0500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[15] <= 0.2814f) {
              if (x[3] <= 95.9500f) {
                votes[0] += 0.0266f;
                votes[1] += 0.9734f;
              } else {
                votes[0] += 0.1305f;
                votes[1] += 0.8695f;
              }
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      } else {
        if (x[17] <= 0.7314f) {
          votes[0] += 1.0000f;
        } else {
          if (x[14] <= -0.2000f) {
            if (x[16] <= 0.1833f) {
              votes[0] += 0.0984f;
              votes[1] += 0.9016f;
            } else {
              votes[0] += 0.0191f;
              votes[1] += 0.9809f;
            }
          } else {
            if (x[15] <= 0.9171f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      }
    }
  } else {
    if (x[7] <= 7.9500f) {
      if (x[4] <= 0.5000f) {
        if (x[5] <= -0.5500f) {
          if (x[0] <= 28.6500f) {
            if (x[10] <= -0.0500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[2] <= 21.7000f) {
                if (x[17] <= -0.1400f) {
                  votes[0] += 0.0266f;
                  votes[1] += 0.9734f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[17] <= -0.4443f) {
                  votes[0] += 0.1730f;
                  votes[1] += 0.8270f;
                } else {
                  votes[0] += 0.7157f;
                  votes[1] += 0.2843f;
                }
              }
            }
          } else {
            if (x[1] <= 1.7500f) {
              if (x[6] <= 4.1000f) {
                if (x[17] <= 0.2543f) {
                  votes[0] += 0.0212f;
                  votes[1] += 0.9788f;
                } else {
                  votes[0] += 0.0837f;
                  votes[1] += 0.9163f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[12] <= 0.1000f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[15] <= 0.8643f) {
            if (x[8] <= -0.0500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[12] <= 0.0875f) {
                if (x[3] <= 65.6500f) {
                  votes[0] += 0.0834f;
                  votes[1] += 0.9166f;
                } else {
                  votes[0] += 0.4849f;
                  votes[1] += 0.5151f;
                }
              } else {
                if (x[15] <= 0.4229f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.5181f;
                  votes[1] += 0.4819f;
                }
              }
            }
          } else {
            if (x[9] <= 0.2500f) {
              if (x[17] <= 1.2614f) {
                if (x[3] <= 76.0000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1106f;
                  votes[1] += 0.8894f;
                }
              } else {
                if (x[13] <= -0.1500f) {
                  votes[0] += 0.3294f;
                  votes[1] += 0.6706f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[5] <= 1.8500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        }
      } else {
        if (x[15] <= 1.4214f) {
          if (x[5] <= -5.9500f) {
            if (x[3] <= 85.3500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 0.0984f;
              votes[1] += 0.9016f;
            }
          } else {
            if (x[10] <= 0.1500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[16] <= 0.3167f) {
                if (x[5] <= 1.8000f) {
                  votes[0] += 0.1407f;
                  votes[1] += 0.8593f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[10] <= -0.2500f) {
            votes[0] += 1.0000f;
          } else {
            if (x[13] <= 0.0500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[16] <= 1.7500f) {
                if (x[14] <= -0.2500f) {
                  votes[0] += 0.0456f;
                  votes[1] += 0.9544f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        }
      }
    } else {
      if (x[6] <= 1.7500f) {
        votes[0] += 1.0000f;
      } else {
        if (x[14] <= -0.7000f) {
          votes[0] += 1.0000f;
        } else {
          if (x[18] <= 0.9667f) {
            if (x[11] <= 4.0250f) {
              votes[0] += 0.0639f;
              votes[1] += 0.9361f;
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[5] <= 5.2000f) {
              votes[0] += 0.0266f;
              votes[1] += 0.9734f;
            } else {
              votes[1] += 1.0000f;
            }
          }
        }
      }
    }
  }
}

static inline void aiPohon16(const float* x, float* votes) {
  if (x[9] <= 0.4500f) {
    if (x[16] <= 0.1833f) {
      if (x[6] <= -2.9500f) {
        votes[0] += 1.0000f;
      } else {
        if (x[11] <= -1.8625f) {
          if (x[2] <= 25.1500f) {
            if (x[10] <= 0.0500f) {
              if (x[0] <= 2.7000f) {
                votes[0] += 0.1392f;
                votes[1] += 0.8608f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[3] <= 78.6000f) {
                votes[0] += 1.0000f;
              } else {
                if (x[6] <= -0.2500f) {
                  votes[0] += 0.1863f;
                  votes[1] += 0.8137f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[3] <= 76.9500f) {
              if (x[5] <= -3.8500f) {
                if (x[7] <= -2.2000f) {
                  votes[0] += 0.1681f;
                  votes[1] += 0.8319f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[11] <= -1.9125f) {
                  votes[0] += 0.8397f;
                  votes[1] += 0.1603f;
                } else {
                  votes[0] += 0.0973f;
                  votes[1] += 0.9027f;
                }
              }
            } else {
              if (x[7] <= -1.8500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[0] <= 11.4000f) {
                  votes[0] += 0.0237f;
                  votes[1] += 0.9763f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        } else {
          if (x[2] <= 25.1500f) {
            if (x[10] <= -0.2500f) {
              if (x[18] <= 0.0833f) {
                if (x[2] <= 20.3500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[15] <= 0.2829f) {
                  votes[0] += 0.0862f;
                  votes[1] += 0.9138f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[16] <= 0.1500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[14] <= -2.6500f) {
                  votes[0] += 0.1952f;
                  votes[1] += 0.8048f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[7] <= 1.3500f) {
              if (x[18] <= -0.5833f) {
                if (x[14] <= -0.8000f) {
                  votes[0] += 0.0631f;
                  votes[1] += 0.9369f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[3] <= 62.5500f) {
                  votes[0] += 0.6469f;
                  votes[1] += 0.3531f;
                } else {
                  votes[0] += 0.9196f;
                  votes[1] += 0.0804f;
                }
              }
            } else {
              if (x[16] <= 0.1500f) {
                if (x[5] <= 0.7500f) {
                  votes[0] += 0.4781f;
                  votes[1] += 0.5219f;
                } else {
                  votes[0] += 0.9034f;
                  votes[1] += 0.0966f;
                }
              } else {
                if (x[8] <= 0.0500f) {
                  votes[0] += 0.6629f;
                  votes[1] += 0.3371f;
                } else {
                  votes[0] += 0.1539f;
                  votes[1] += 0.8461f;
                }
              }
            }
          }
        }
      }
    } else {
      if (x[15] <= 0.9986f) {
        if (x[9] <= -0.3500f) {
          votes[0] += 1.0000f;
        } else {
          if (x[6] <= 4.3500f) {
            if (x[0] <= 26.6500f) {
              if (x[5] <= -5.8500f) {
                if (x[7] <= -1.9500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0450f;
                  votes[1] += 0.9550f;
                }
              } else {
                if (x[6] <= 0.3500f) {
                  votes[0] += 0.8432f;
                  votes[1] += 0.1568f;
                } else {
                  votes[0] += 0.5796f;
                  votes[1] += 0.4204f;
                }
              }
            } else {
              if (x[2] <= 22.8500f) {
                if (x[7] <= 1.1500f) {
                  votes[0] += 0.3721f;
                  votes[1] += 0.6279f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[17] <= 1.6743f) {
                  votes[0] += 0.0960f;
                  votes[1] += 0.9040f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[3] <= 64.8000f) {
              if (x[0] <= 15.8500f) {
                votes[0] += 0.0973f;
                votes[1] += 0.9027f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      } else {
        if (x[16] <= 0.2167f) {
          votes[0] += 0.0690f;
          votes[1] += 0.9310f;
        } else {
          if (x[15] <= 1.4529f) {
            votes[0] += 1.0000f;
          } else {
            if (x[0] <= 51.0000f) {
              votes[0] += 0.1392f;
              votes[1] += 0.8608f;
            } else {
              if (x[14] <= -2.1000f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        }
      }
    }
  } else {
    if (x[1] <= 1.1500f) {
      votes[0] += 1.0000f;
    } else {
      if (x[5] <= 5.0500f) {
        if (x[12] <= 0.4000f) {
          if (x[10] <= 2.4500f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 0.1587f;
            votes[1] += 0.8413f;
          }
        } else {
          votes[0] += 0.0670f;
          votes[1] += 0.9330f;
        }
      } else {
        if (x[16] <= 1.4833f) {
          if (x[6] <= 12.8500f) {
            votes[1] += 1.0000f;
          } else {
            votes[1] += 1.0000f;
          }
        } else {
          if (x[2] <= 28.5000f) {
            votes[0] += 0.0133f;
            votes[1] += 0.9867f;
          } else {
            votes[1] += 1.0000f;
          }
        }
      }
    }
  }
}

static inline void aiPohon17(const float* x, float* votes) {
  if (x[1] <= 0.6500f) {
    if (x[2] <= 29.2500f) {
      if (x[6] <= 5.3500f) {
        if (x[5] <= -0.4500f) {
          if (x[17] <= 0.0643f) {
            if (x[3] <= 94.3500f) {
              if (x[5] <= -1.3500f) {
                if (x[16] <= 0.0167f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[0] <= 7.2500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.3880f;
                  votes[1] += 0.6120f;
                }
              }
            } else {
              if (x[6] <= 0.3000f) {
                if (x[9] <= -0.2500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[6] <= 2.2000f) {
                  votes[0] += 0.1368f;
                  votes[1] += 0.8632f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[3] <= 69.9500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[3] <= 88.5500f) {
                if (x[14] <= -1.6500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.3170f;
                  votes[1] += 0.6830f;
                }
              } else {
                if (x[1] <= 0.2500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        } else {
          if (x[0] <= 30.5500f) {
            if (x[11] <= -0.9625f) {
              if (x[11] <= -1.0875f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 0.1745f;
                votes[1] += 0.8255f;
              }
            } else {
              if (x[0] <= 4.5500f) {
                if (x[9] <= 0.1500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1745f;
                  votes[1] += 0.8255f;
                }
              } else {
                if (x[14] <= -0.2500f) {
                  votes[0] += 0.9283f;
                  votes[1] += 0.0717f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            if (x[3] <= 88.5000f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 0.1312f;
              votes[1] += 0.8688f;
            }
          }
        }
      } else {
        if (x[18] <= 0.1500f) {
          if (x[18] <= -0.2833f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[10] <= 0.0500f) {
            if (x[1] <= 0.4500f) {
              if (x[0] <= 13.0500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              votes[0] += 0.0236f;
              votes[1] += 0.9764f;
            }
          } else {
            if (x[1] <= 0.3500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      }
    } else {
      if (x[11] <= 2.3125f) {
        if (x[0] <= 8.9500f) {
          if (x[13] <= 0.1500f) {
            if (x[2] <= 30.2500f) {
              if (x[11] <= -1.1750f) {
                if (x[3] <= 64.7500f) {
                  votes[0] += 0.1641f;
                  votes[1] += 0.8359f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[16] <= 0.0833f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[2] <= 30.5500f) {
              if (x[6] <= -3.2500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[2] <= 29.8500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0636f;
                  votes[1] += 0.9364f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          }
        } else {
          if (x[10] <= 0.0500f) {
            if (x[14] <= 2.1500f) {
              if (x[17] <= -0.3129f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[11] <= -2.4250f) {
                votes[0] += 0.1312f;
                votes[1] += 0.8688f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[12] <= -0.1250f) {
              if (x[17] <= 0.3671f) {
                if (x[6] <= 1.4500f) {
                  votes[0] += 0.1676f;
                  votes[1] += 0.8324f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[17] <= 0.4314f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      } else {
        if (x[9] <= -0.0500f) {
          if (x[12] <= -0.2375f) {
            if (x[15] <= 0.5514f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 0.0831f;
              votes[1] += 0.9169f;
            }
          } else {
            if (x[0] <= 7.8500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          }
        } else {
          if (x[8] <= 0.2500f) {
            if (x[14] <= 1.3500f) {
              if (x[13] <= -0.2500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[12] <= -0.1625f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1246f;
                  votes[1] += 0.8754f;
                }
              }
            } else {
              if (x[8] <= -0.0500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[5] <= 2.8500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          }
        }
      }
    }
  } else {
    if (x[9] <= 0.5500f) {
      if (x[9] <= -0.3500f) {
        votes[0] += 1.0000f;
      } else {
        if (x[17] <= 0.9071f) {
          if (x[16] <= 0.5167f) {
            if (x[0] <= 27.3500f) {
              if (x[15] <= 0.5043f) {
                if (x[14] <= 0.2500f) {
                  votes[0] += 0.3211f;
                  votes[1] += 0.6789f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[15] <= 0.7443f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.6879f;
                  votes[1] += 0.3121f;
                }
              }
            } else {
              if (x[2] <= 30.6500f) {
                if (x[7] <= -0.1500f) {
                  votes[0] += 0.1276f;
                  votes[1] += 0.8724f;
                } else {
                  votes[0] += 0.2710f;
                  votes[1] += 0.7290f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[2] <= 22.1500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          }
        } else {
          if (x[6] <= 4.2500f) {
            if (x[4] <= 0.5000f) {
              if (x[15] <= 0.8243f) {
                if (x[7] <= 3.9500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.3257f;
                  votes[1] += 0.6743f;
                }
              } else {
                if (x[5] <= 3.2500f) {
                  votes[0] += 0.3521f;
                  votes[1] += 0.6479f;
                } else {
                  votes[0] += 0.1182f;
                  votes[1] += 0.8818f;
                }
              }
            } else {
              if (x[2] <= 29.7500f) {
                if (x[7] <= 4.5500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.7046f;
                  votes[1] += 0.2954f;
                }
              } else {
                if (x[18] <= 0.5833f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2319f;
                  votes[1] += 0.7681f;
                }
              }
            }
          } else {
            if (x[13] <= 0.4500f) {
              if (x[8] <= -0.2500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[7] <= 1.7500f) {
                votes[0] += 0.1312f;
                votes[1] += 0.8688f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        }
      }
    } else {
      if (x[10] <= 1.0500f) {
        votes[0] += 0.0569f;
        votes[1] += 0.9431f;
      } else {
        if (x[8] <= 0.5500f) {
          votes[0] += 0.0569f;
          votes[1] += 0.9431f;
        } else {
          if (x[17] <= 1.9900f) {
            votes[0] += 0.0149f;
            votes[1] += 0.9851f;
          } else {
            votes[1] += 1.0000f;
          }
        }
      }
    }
  }
}

static inline void aiPohon18(const float* x, float* votes) {
  if (x[15] <= 0.7814f) {
    if (x[2] <= 25.1500f) {
      if (x[16] <= 0.0167f) {
        if (x[5] <= -1.4500f) {
          votes[0] += 0.0505f;
          votes[1] += 0.9495f;
        } else {
          if (x[6] <= -1.6000f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      } else {
        if (x[3] <= 94.4500f) {
          if (x[6] <= -6.4500f) {
            if (x[16] <= 0.1167f) {
              if (x[3] <= 71.0500f) {
                votes[0] += 0.1376f;
                votes[1] += 0.8624f;
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[13] <= -0.2500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[9] <= -0.3500f) {
              if (x[10] <= -0.0500f) {
                if (x[1] <= 0.1500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                votes[0] += 0.0961f;
                votes[1] += 0.9039f;
              }
            } else {
              if (x[13] <= 0.0500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[9] <= -0.0500f) {
                  votes[0] += 0.8231f;
                  votes[1] += 0.1769f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        } else {
          if (x[0] <= 8.9000f) {
            if (x[17] <= -0.2400f) {
              if (x[11] <= -3.0875f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 0.1569f;
                votes[1] += 0.8431f;
              }
            } else {
              if (x[9] <= -0.2500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[5] <= -2.3000f) {
              if (x[7] <= -3.3500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 0.0157f;
                votes[1] += 0.9843f;
              }
            } else {
              if (x[5] <= 5.7000f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 0.0961f;
                votes[1] += 0.9039f;
              }
            }
          }
        }
      }
    } else {
      if (x[7] <= 5.5500f) {
        if (x[17] <= 0.5014f) {
          if (x[7] <= -2.3500f) {
            if (x[3] <= 64.3500f) {
              if (x[17] <= -0.1643f) {
                if (x[11] <= -3.8125f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0784f;
                  votes[1] += 0.9216f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            } else {
              if (x[13] <= -0.5500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[2] <= 25.6500f) {
              if (x[11] <= -3.6750f) {
                votes[0] += 1.0000f;
              } else {
                if (x[0] <= 7.7500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1225f;
                  votes[1] += 0.8775f;
                }
              }
            } else {
              if (x[18] <= 0.4833f) {
                if (x[7] <= -2.2500f) {
                  votes[0] += 0.1139f;
                  votes[1] += 0.8861f;
                } else {
                  votes[0] += 0.6045f;
                  votes[1] += 0.3955f;
                }
              } else {
                votes[0] += 1.0000f;
              }
            }
          }
        } else {
          if (x[5] <= 2.1500f) {
            if (x[16] <= 0.0500f) {
              if (x[5] <= 1.2500f) {
                votes[0] += 0.1174f;
                votes[1] += 0.8826f;
              } else {
                if (x[13] <= -0.1000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[17] <= 0.7129f) {
              votes[0] += 1.0000f;
            } else {
              if (x[5] <= 2.8500f) {
                if (x[5] <= 2.7500f) {
                  votes[0] += 0.5555f;
                  votes[1] += 0.4445f;
                } else {
                  votes[0] += 0.0814f;
                  votes[1] += 0.9186f;
                }
              } else {
                if (x[5] <= 4.4500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.6281f;
                  votes[1] += 0.3719f;
                }
              }
            }
          }
        }
      } else {
        if (x[9] <= 0.0500f) {
          if (x[8] <= -0.1500f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[8] <= 0.1500f) {
            if (x[0] <= 13.9000f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[1] <= 0.9500f) {
              votes[0] += 0.0309f;
              votes[1] += 0.9691f;
            } else {
              votes[1] += 1.0000f;
            }
          }
        }
      }
    }
  } else {
    if (x[5] <= 10.0500f) {
      if (x[0] <= 34.9500f) {
        if (x[9] <= -0.3500f) {
          votes[0] += 1.0000f;
        } else {
          if (x[3] <= 85.7500f) {
            if (x[2] <= 30.7000f) {
              if (x[0] <= 29.9500f) {
                if (x[7] <= 1.7500f) {
                  votes[0] += 0.1406f;
                  votes[1] += 0.8594f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[13] <= -0.6500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.0533f;
                  votes[1] += 0.9467f;
                }
              }
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[16] <= 0.2167f) {
              votes[0] += 1.0000f;
            } else {
              if (x[0] <= 29.3500f) {
                if (x[2] <= 23.1000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.3472f;
                  votes[1] += 0.6528f;
                }
              } else {
                if (x[2] <= 21.9500f) {
                  votes[0] += 0.5756f;
                  votes[1] += 0.4244f;
                } else {
                  votes[0] += 0.1868f;
                  votes[1] += 0.8132f;
                }
              }
            }
          }
        }
      } else {
        if (x[18] <= 2.9500f) {
          if (x[2] <= 29.7500f) {
            if (x[14] <= 3.3500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[15] <= 1.2143f) {
                votes[0] += 0.1376f;
                votes[1] += 0.8624f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[2] <= 29.8500f) {
              if (x[12] <= 0.1875f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 0.0623f;
                votes[1] += 0.9377f;
              }
            } else {
              if (x[1] <= 1.7500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[10] <= -0.8000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1174f;
                  votes[1] += 0.8826f;
                }
              }
            }
          }
        } else {
          if (x[10] <= 3.5000f) {
            votes[0] += 0.0105f;
            votes[1] += 0.9895f;
          } else {
            votes[1] += 1.0000f;
          }
        }
      }
    } else {
      if (x[1] <= 0.5500f) {
        votes[0] += 1.0000f;
      } else {
        if (x[7] <= 11.1500f) {
          votes[0] += 1.0000f;
        } else {
          if (x[1] <= 1.6500f) {
            votes[0] += 0.0445f;
            votes[1] += 0.9555f;
          } else {
            votes[1] += 1.0000f;
          }
        }
      }
    }
  }
}

static inline void aiPohon19(const float* x, float* votes) {
  if (x[16] <= 0.2167f) {
    if (x[16] <= 0.0833f) {
      if (x[15] <= 0.0471f) {
        votes[0] += 0.2873f;
        votes[1] += 0.7127f;
      } else {
        if (x[14] <= 2.9500f) {
          if (x[10] <= -0.2500f) {
            if (x[2] <= 25.0500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[3] <= 74.4500f) {
                if (x[15] <= 0.1586f) {
                  votes[0] += 0.1784f;
                  votes[1] += 0.8216f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[17] <= 0.6100f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.1104f;
                  votes[1] += 0.8896f;
                }
              }
            }
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[5] <= -1.3000f) {
            votes[0] += 0.1988f;
            votes[1] += 0.8012f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      }
    } else {
      if (x[0] <= 4.0500f) {
        if (x[8] <= 0.0500f) {
          if (x[13] <= -0.3500f) {
            if (x[2] <= 24.1500f) {
              votes[0] += 1.0000f;
            } else {
              votes[0] += 0.1569f;
              votes[1] += 0.8431f;
            }
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[15] <= 0.0757f) {
            votes[0] += 1.0000f;
          } else {
            if (x[10] <= 0.1500f) {
              if (x[12] <= 0.1875f) {
                votes[0] += 0.0851f;
                votes[1] += 0.9149f;
              } else {
                votes[0] += 0.0444f;
                votes[1] += 0.9556f;
              }
            } else {
              votes[0] += 0.1988f;
              votes[1] += 0.8012f;
            }
          }
        }
      } else {
        if (x[6] <= 22.3000f) {
          if (x[12] <= -0.4625f) {
            if (x[3] <= 66.6000f) {
              votes[0] += 0.0373f;
              votes[1] += 0.9627f;
            } else {
              votes[0] += 1.0000f;
            }
          } else {
            if (x[11] <= -7.3250f) {
              if (x[7] <= -0.1500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[17] <= -0.5829f) {
                  votes[0] += 0.0584f;
                  votes[1] += 0.9416f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[8] <= 0.2500f) {
                if (x[6] <= 1.6500f) {
                  votes[0] += 0.6691f;
                  votes[1] += 0.3309f;
                } else {
                  votes[0] += 0.9382f;
                  votes[1] += 0.0618f;
                }
              } else {
                if (x[14] <= -2.5500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          }
        } else {
          if (x[6] <= 52.0500f) {
            votes[0] += 0.0242f;
            votes[1] += 0.9758f;
          } else {
            votes[0] += 1.0000f;
          }
        }
      }
    }
  } else {
    if (x[3] <= 64.2500f) {
      if (x[11] <= -7.0500f) {
        if (x[0] <= 35.3000f) {
          votes[0] += 0.1104f;
          votes[1] += 0.8896f;
        } else {
          votes[0] += 1.0000f;
        }
      } else {
        if (x[9] <= 0.0500f) {
          if (x[14] <= -2.9500f) {
            votes[0] += 1.0000f;
          } else {
            votes[0] += 1.0000f;
          }
        } else {
          if (x[1] <= 1.3500f) {
            if (x[1] <= 0.7500f) {
              if (x[17] <= 0.6171f) {
                votes[0] += 1.0000f;
              } else {
                if (x[0] <= 17.3000f) {
                  votes[0] += 0.0584f;
                  votes[1] += 0.9416f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            } else {
              if (x[7] <= -15.3500f) {
                votes[0] += 1.0000f;
              } else {
                votes[0] += 1.0000f;
              }
            }
          } else {
            if (x[10] <= 0.0500f) {
              votes[0] += 1.0000f;
            } else {
              if (x[15] <= 1.2171f) {
                votes[0] += 0.1104f;
                votes[1] += 0.8896f;
              } else {
                votes[0] += 0.1988f;
                votes[1] += 0.8012f;
              }
            }
          }
        }
      }
    } else {
      if (x[5] <= 7.2500f) {
        if (x[11] <= 3.5375f) {
          if (x[3] <= 79.1500f) {
            if (x[18] <= 2.8167f) {
              if (x[10] <= -0.0500f) {
                if (x[5] <= -6.7500f) {
                  votes[0] += 0.3886f;
                  votes[1] += 0.6114f;
                } else {
                  votes[0] += 1.0000f;
                }
              } else {
                if (x[4] <= 0.5000f) {
                  votes[0] += 0.2218f;
                  votes[1] += 0.7782f;
                } else {
                  votes[0] += 0.9242f;
                  votes[1] += 0.0758f;
                }
              }
            } else {
              votes[1] += 1.0000f;
            }
          } else {
            if (x[0] <= 27.3500f) {
              if (x[5] <= -3.7500f) {
                if (x[9] <= 0.0500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2456f;
                  votes[1] += 0.7544f;
                }
              } else {
                if (x[14] <= -2.4500f) {
                  votes[0] += 0.1342f;
                  votes[1] += 0.8658f;
                } else {
                  votes[0] += 0.8327f;
                  votes[1] += 0.1673f;
                }
              }
            } else {
              if (x[7] <= -10.1500f) {
                votes[0] += 1.0000f;
              } else {
                if (x[0] <= 34.7500f) {
                  votes[0] += 0.1351f;
                  votes[1] += 0.8649f;
                } else {
                  votes[0] += 0.7949f;
                  votes[1] += 0.2051f;
                }
              }
            }
          }
        } else {
          if (x[15] <= 0.9957f) {
            if (x[3] <= 82.9500f) {
              if (x[14] <= -1.9000f) {
                votes[0] += 0.0301f;
                votes[1] += 0.9699f;
              } else {
                if (x[5] <= 4.2500f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 0.2766f;
                  votes[1] += 0.7234f;
                }
              }
            } else {
              if (x[14] <= -1.6000f) {
                votes[0] += 0.2543f;
                votes[1] += 0.7457f;
              } else {
                if (x[5] <= 2.4000f) {
                  votes[0] += 1.0000f;
                } else {
                  votes[0] += 1.0000f;
                }
              }
            }
          } else {
            votes[0] += 1.0000f;
          }
        }
      } else {
        if (x[8] <= 0.2500f) {
          votes[0] += 1.0000f;
        } else {
          if (x[18] <= 1.2833f) {
            votes[0] += 0.1784f;
            votes[1] += 0.8216f;
          } else {
            votes[1] += 1.0000f;
          }
        }
      }
    }
  }
}

// Mengembalikan peluang (0..1) bahwa udara akan memburuk.
inline float aiPeluangMemburuk(const float* x) {
  float votes[2] = {0, 0};
  aiPohon0(x, votes);
  aiPohon1(x, votes);
  aiPohon2(x, votes);
  aiPohon3(x, votes);
  aiPohon4(x, votes);
  aiPohon5(x, votes);
  aiPohon6(x, votes);
  aiPohon7(x, votes);
  aiPohon8(x, votes);
  aiPohon9(x, votes);
  aiPohon10(x, votes);
  aiPohon11(x, votes);
  aiPohon12(x, votes);
  aiPohon13(x, votes);
  aiPohon14(x, votes);
  aiPohon15(x, votes);
  aiPohon16(x, votes);
  aiPohon17(x, votes);
  aiPohon18(x, votes);
  aiPohon19(x, votes);
  return votes[1] / 20.0f;
}