using System;
using System.Collections.Generic;
using System.Text;

namespace E4Gamma
{
    public struct EGVector
    {
        float m_x, m_y, m_z;

        static public EGVector I
        {
            get
            {
                return new EGVector(1, 0, 0);
            }
        }

        static public EGVector J
        {
            get
            {
                return new EGVector(0, 1, 0);
            }
        }

        static public EGVector K
        {
            get
            {
                return new EGVector(0, 0, 1);
            }
        }

        public EGVector(float fx, float fy, float fz)
        {
            m_x = fx;
            m_y = fy;
            m_z = fz;
        }

        public float Length()
        {
            return (float)Math.Sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
        }
    }
}
