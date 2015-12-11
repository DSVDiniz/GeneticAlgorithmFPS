#ifndef POINT_H_
	#define POINT_H_

template <class T>
class Point
{
	public:
		Point(T a=0, T b=0, T c=0, T tp=0, T vol=0):x(a),y(b),z(c),t(tp),v(vol) {};
		~Point()
		{
			x=y=z=t=v=0;
		};

		//seta novos valores a um ponto
		void set(T a=0, T b=0, T c=0, T tp=0, T vol=0)
		{
			x=a;
			y=b;
			z=c;
			t=tp;
			v=vol;
		};
		void set(Point a)
		{
			x=a.x;
			y=a.y;
			z=a.z;
			t=a.t;
			v=a.v;
		};
		void setY(T b)
		{
			y=b;
		};
		void setZ(T c)
		{
			z=c;
		};
		void setT(T tipo)
		{
			t=tipo;
		};

		//soma valores a um ponto
		void add(T a=0, T b=0, T c=0)
		{
			x+=a;
			y+=b;
			z+=c;
		};

		void add(Point a)
		{
			x+=a.x;
			y+=a.y;
			z+=a.z;
		};

		void sub(T a=0, T b=0, T c=0)
		{
			x-=a.x;
			y-=a.y;
			z-=a.z;
		};

		void sub(Point a)
		{
			x-=a.x;
			y-=a.y;
			z-=a.z;
		};

		void mul(T a)
		{
			x*=a;
			y*=a;
			z*=a;
		};

		void scalar(T a, T b, T c)
		{
			x*=a;
			y*=b;
			z*=c;
		};

		//compara a outro ponto
		bool comp(Point a)
		{
			if((a.x==x)&&(a.y==y)&&(a.z==z))
				return true;
			else
				return false;
		}
		bool comp(T a, T b, T c, T d)
		{
			if((a==x)&&(b==y)&&(c==z)&&(d==t))
				return true;
			else
				return false;
		}

		T x;
		T y;
		T z;
		T t;
		T v;
};
#endif /*POINT_H_*/
