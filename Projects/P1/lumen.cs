// Alen Ovalles
// lumen.cs
// 4/4/2023
// CPSC 3200

using System;
namespace P1
{
    public class Lumen
    {
        private const int LOW_POWER = 0;
        private const int GLOW_RESET_VALUE = 2;
        private const int DEFAULT_BRIGHTNESS = 7;
        private const int DEFAULT_POWER = 7;
        private const int DEFAULT_SIZE = 5;
        private int initialBrightness;
        private int actualBrightness;
        private int initialPower;   
        private int actualPower;
        private int size;
        private int glowRequests;
        private bool active;
        private bool stable;
        
        public Lumen(int inputSize)
        {
            if(inputSize <= 0 || inputSize > 10)
            {
                inputSize = DEFAULT_SIZE;
            }

            initialBrightness = actualBrightness = DEFAULT_BRIGHTNESS;
            initialPower = actualPower = DEFAULT_POWER;
            size = inputSize;
            active = true;
            stable = true;
            glowRequests = 0;
        }

        public int glow()
        {
            if(active)
            {  
                glowRequests++;
                actualPower--;
                return size * actualPower;
            }
            if(stable)
            {
                return actualBrightness;
            }
            return actualPower;
        }
        public bool reset()
        {
            if(actualPower > LOW_POWER && glowRequests >= GLOW_RESET_VALUE)
            {
                actualBrightness = initialBrightness;
                actualPower = initialPower;
                glowRequests = 0;
                active = true;
                return true;
            }
           
            actualBrightness--;
            return false;
            
        }
        public bool isActive()
        {
            if(actualPower <= LOW_POWER){
                active = false;
                stable = false;
            }
            return active;
        }
    }
}