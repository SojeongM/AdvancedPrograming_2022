import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import find_peaks
from scipy.interpolate import splprep, splev
from scipy.optimize import minimize
import time


class LateralController:
    '''
    Lateral control using the Stanley controller

    functions:
        stanley 

    init:
        gain_constant (default=5)
        damping_constant (default=0.5)
    '''


    def __init__(self, gain_constant=5, damping_constant=0.6):

        self.gain_constant = gain_constant
        self.damping_constant = damping_constant
        self.previous_steering_angle = 0


    def stanley(self, waypoints, speed):
        '''
        ##### TODO #####
        one step of the stanley controller with damping
        args:
            waypoints (np.array) [2, num_waypoints]
            speed (float)
        '''
        num=48
        AR=np.array([num, 0])
        p = waypoints[:, 1] - AR
        q = waypoints[:, 0] - AR
        
        y = p - q
        

        # derive cross track error as distance between desired waypoint at spline parameter equal zero ot the car position
        # (48,0 is the position of the car). Since we only want lateral distance,
        # the cross track error is the difference between the first waypoint's x dimention & 48.
      
        z = np.arctan(y[0] / y[1])
        # derive stanley control law
        # prevent division by zero by adding as small epsilon
        xy = z + np.arctan(self.gain_constant * (waypoints[0, 0] - num) / (speed + 0.00001) )

        # derive damping term
        x = xy - (self.damping_constant * (xy - self.previous_steering_angle))
        
        self.previous_steering_angle = x
      #  print(x)
       # print()
        if x>0.4:
            return 0.4
        elif x<-0.4:
            return -0.4
        else:
            return x
        # clip to the maximum stering angle (0.4) and rescale the steering action space
    #    return np.clip(x, -0.4, 0.4) / 0.8

       
        # derive damping term
        
        # clip to the maximum stering angle (0.4) and rescale the steering action space
        
        # derive orientation error as the angle of the first path segment to the car orientation

        # derive stanley control law
        # derive cross track error as distance between desired waypoint at spline parameter equal zero ot the car position
        # prevent division by zero by adding as small epsilon 
        # derive damping
        
        # clip to the maximum stering angle (0.4) and rescale the steering action space






