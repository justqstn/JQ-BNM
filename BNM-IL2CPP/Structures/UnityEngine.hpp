#pragma once
#include <math.h>
#include <cstdint>
#define M_PI       3.14159265358979323846

namespace Unity
{
    struct Vector3
    {
        float x;
        float y;
        float z;

        Vector3() { x = y = z = 0.f; }
        Vector3(float f1, float f2, float f3)
        {
            x = f1;
            y = f2;
            z = f3;
        }

        float Length()
        {
            return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        }

        static float Distance(Vector3 &a, Vector3 &b)
        {

            return Vector3(b.x - a.x, b.y - a.y, b.z - a.z).Length();
        }

        float Dot(Vector3 b)
		{
			return x * b.x + y * b.y + z * b.z;
		}

		Vector3 Normalize()
		{
			float len = Length();
			if (len > 0)
				return Vector3(x / len, y / len, z / len);
			else
				return Vector3(x, y, z);
		}
    };

    struct Vector2
    {
        float x;
        float y;

        Vector2() { x = y = 0.f; }
        Vector2(float f1, float f2)
        {
            x = f1;
            y = f2;
        }

        float Length()
        {
            return std::sqrt(this->x * this->x + this->y * this->y);
        }

        static float Distance(Vector2 &a, Vector2 &b)
        {

            return Vector2(b.x - a.x, b.y - a.y).Length();
        }
    };

    struct Quaternion
    {
        float x, y, z, w;

        Quaternion() { x = y = z = w = 0.f; }
        Quaternion(float f1, float f2, float f3, float f4) { x = f1; y = f2; z = f3; w = f4; }

        Quaternion Euler(float m_fX, float m_fY, float m_fZ)
        {
            float m_fDeg2Rad = static_cast<float>(M_PI) / 180.f;

            m_fX = m_fX * m_fDeg2Rad * 0.5f;
            m_fY = m_fY * m_fDeg2Rad * 0.5f;
            m_fZ = m_fZ * m_fDeg2Rad * 0.5f;

            float m_fSinX = sinf(m_fX);
            float m_fCosX = cosf(m_fX);

            float m_fSinY = sinf(m_fY);
            float m_fCosY = cosf(m_fY);

            float m_fSinZ = sinf(m_fZ);
            float m_fCosZ = cosf(m_fZ);

            x = m_fCosY * m_fSinX * m_fCosZ + m_fSinY * m_fCosX * m_fSinZ;
            y = m_fSinY * m_fCosX * m_fCosZ - m_fCosY * m_fSinX * m_fSinZ;
            z = m_fCosY * m_fCosX * m_fSinZ - m_fSinY * m_fSinX * m_fCosZ;
            w = m_fCosY * m_fCosX * m_fCosZ + m_fSinY * m_fSinX * m_fSinZ;

            return *this;
        }

        Quaternion Euler(Vector3 m_vRot)
        {
            return Euler(m_vRot.x, m_vRot.y, m_vRot.z);
        }

        Vector3 ToEuler()
        {
            Vector3 m_vEuler;

            float m_fDist = (x * x) + (y * y) + (z * z) + (w * w);

            float m_fTest = x * w - y * z;
            if (m_fTest > 0.4995f * m_fDist)
            {
                m_vEuler.x = static_cast<float>(M_PI) * 0.5f;
                m_vEuler.y = 2.f * atan2f(y, x);
                m_vEuler.z = 0.f;
            }
            else if (m_fTest < -0.4995f * m_fDist)
            {
                m_vEuler.x = static_cast<float>(M_PI) * -0.5f;
                m_vEuler.y = -2.f * atan2f(y, x);
                m_vEuler.z = 0.f;
            }
            else
            {
                m_vEuler.x = asinf(2.f * (w * x - y * z));
                m_vEuler.y = atan2f(2.f * w * y + 2.f * z * x, 1.f - 2.f * (x * x + y * y));
                m_vEuler.z = atan2f(2.f * w * z + 2.f * x * y, 1.f - 2.f * (z * z + x * x));
            }

            float m_fRad2Deg = 180.f / static_cast<float>(M_PI);
            m_vEuler.x *= m_fRad2Deg;
            m_vEuler.y *= m_fRad2Deg;
            m_vEuler.z *= m_fRad2Deg;

            return m_vEuler;
        }
    };

    struct Ray
    {
        Vector3 Origin;
        Vector3 Direction;
    };

    struct RaycastHit
    {
        Vector3 Point;
        Vector3 Normal;
        uint64_t face_id;
        float distance;
        Vector2 UV;
        int collider;
    };

    struct Color
    {
        float r, g, b, a;

        Color() { r = g = b = a = 0.f; }
        Color(float fRed = 0.f, float fGreen = 0.f, float fBlue = 0.f, float fAlpha = 1.f)
        {
            r = fRed;
            g = fGreen;
            b = fBlue;
            a = fAlpha;
        }
    };
}