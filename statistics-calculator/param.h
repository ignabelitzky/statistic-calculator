#ifndef PARAM_H
#define PARAM_H

enum display_output {
                      ARITHMETIC_MEAN = (1u << 0),
                      MEDIAN = (1u << 1),
                      MINIMUM = (1u << 2),
                      MAXIMUM = (1u << 3),
                      VARIANCE = (1u << 4),
                      STANDARD_DEVIATION = (1u << 5),
                      LOWER_QUARTILE = (1u << 6),
                      UPPER_QUARTILE = (1u << 7),
                      ALL = (255u)
                    };

#endif // PARAM_H
