/*
 * TinyEKF: Extended Kalman Filter for Arduino and TeensyBoard.
 *
 * Copyright (C) 2015 Simon D. Levy
 *
 * This code is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this code.  If not, see <http:#www.gnu.org/licenses/>.
 */

#include "tinyekf.h"

/**
  * A class for the Extended Kalman Filter.
  */
class TinyEKF {

    private:

        ekf_t ekf;

    protected:

        /**
        * State vector, length <i>n</i>.
        */
        double * x;

        /**
          * Initializes a TinyEKF object.
          */
        TinyEKF();

        /**
          * Deallocates memory for a TinyEKF object.
          */
         ~TinyEKF();

         /**
           * Implement this function for your EKF model.
           * @param fx gets output of state-transition function <i>f(x<sub>0 .. n-1</sub>)</i>
           * @param F gets <i>n &times; n</i> Jacobian of <i>f(x)</i>
           * @param hx gets output of observation function <i>h(x<sub>0 .. n-1</sub>)</i>
           * @param H gets <i>m &times; n</i> Jacobian of <i>h(x)</i>
           */
        virtual void model(double fx[N], double F[N][N], double hx[N], double H[M][N]) = 0;

        /**
          * Sets a the value in the state noise covariance matrix <i>P</i>.  
          * Typically done during initialization.  Unset values are zero by default by default.
          * @param i row index (first = 0)
          * @param j row index (first = 0)
          * @param value value to set
          */
         void setP(int i, int j, double value);

        /**
          * Sets a the value in the process noise covariance matrix <i>Q</i>.
          * Typically done during initialization.  Unset values are zero by default by default.
          * @param i row index (first = 0)
          * @param j row index (first = 0)
          * @param value value to set
          */
         void setQ(int i, int j, double value);

        /**
          * Sets a the value in the measurement noise covariance matrix <i>R</i>.
          * Typically done during initialization.  Unset values are zero by default by default.
          * @param i row index (first = 0)
          * @param j row index (first = 0)
          * @param value value to set
          */
         void setR(int i, int j, double value);

    public:

        /**
          * Returns the state element at a given index.
          * @param i the index (at least 0 and less than <i>n</i>
          * @return state value at index
          */
        double getX(int i);

        /**
          Performs one step of the prediction and update.
          * @param z observation vector, length <i>m</i>
          * @return true on success, false on failure caused by non-positive-definite matrix.
         */
        bool step(double * z);
};
