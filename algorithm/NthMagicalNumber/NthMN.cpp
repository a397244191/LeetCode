#define MODNUM 1000000007

int gcd(int a,int b) {
   while((a%=b) && (b%=a));
    return a + b;
}

long long int CheckXthInNth(long long int A,long long int B,long long int AB,long long int N,long long int X) {
    long long int Y,Z;
     Y = A * X / B;
     Z = A * X / AB;
     return N - (X+Y-Z);
}

class Solution {
public:
    int nthMagicalNumber(int N, int A, int B) {
        if(A > B) swap(A,B);
        long long int AB = A*B/gcd(A,B);
        long long int l = 1, r = N;
        while(l <= r) {
            long long int mid = (l+r)/2;
            if(CheckXthInNth(A,B,AB,N,mid) < 0) {
                if(mid - 1 <= l) break;
                else r = mid - 1;
            } else if(CheckXthInNth(A,B,AB,N,mid) > 0) {
                if(mid + 1 >= r) break;
                else l = mid + 1;
            } else {
                return (int)((mid * ((long long int)A))%MODNUM);
            }
        }
        //check r is not corret ans
        if(!CheckXthInNth(A,B,AB,N,r)) return ((r * ((long long int)A))%MODNUM);
        //check l is not corret ans
        if(!CheckXthInNth(A,B,AB,N,l)) return ((l * ((long long int)A))%MODNUM);
        
        l = ((long long int)A) * l / ((long long int)B) - 1;
        l = l < 0 ? 1 : l;
        r = ((long long int)A) * r / ((long long int)B) + 1;
        
        swap(A,B);
        while(l <= r) {
            long long int mid = (l+r)/2;
            if(CheckXthInNth(A,B,AB,N,mid) < 0) {
                if(mid - 1 <= l) break;
                else r = mid - 1;
            } else if(CheckXthInNth(A,B,AB,N,mid) > 0) {
                if(mid + 1 >= r) break;
                else l = mid + 1;
            } else {
                return (int)((mid * ((long long int)A))%MODNUM);
            }
        }
        //check r is not corret ans
        if(!CheckXthInNth(A,B,AB,N,r)) return ((r * ((long long int)A))%MODNUM);
        //check l is not corret ans
        if(!CheckXthInNth(A,B,AB,N,l)) return ((l * ((long long int)A))%MODNUM);
        
        
        return -1;
        
    }
};