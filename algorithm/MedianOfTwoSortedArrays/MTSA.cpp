class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> *n1 = &nums1;
        vector<int> *n2 = &nums2;
        
        if(n1->size() > n2->size())
            swap(n1,n2);
        int n = n1->size(),m = n2->size();
        if(n == 0) {
            if(m % 2) return n2->at(m/2);
            else return ((double)(n2->at(m/2)) + (double)(n2->at(m/2 - 1)))*0.5;
        } 
        bool even = ((n+m)%2 == 0);
        int ltN = (n+m)/2;
        int l = 0, r = n1->size() - 1;
        
        while(l < r) {
            int mid = (l + r) / 2;
            if(n1->at(mid) < n2->at(ltN - mid - 1)) l = mid + 1;
            else if(n1->at(mid) > n2->at(ltN - mid - 1)) r = mid - 1;
            else return (double)(n1->at(mid));
        }
        if(r < 0) r = 0;
        if(l >= n) l = n - 1 ;
        vector<int> ansList;
        if(l == r) {
            if(n1->at(l) > n2->at(ltN - l - 1)){
                if(ltN - l < m && n1->at(l) > n2->at(ltN - l)) {
                    ansList.push_back(n2->at(ltN - l));
                } else {
                    ansList.push_back(n1->at(l));
                }
                if(l > 0 && n1->at(l - 1) > n2->at(ltN - l - 1)) {
                    ansList.push_back(n1->at(l - 1));
                } else {
                    ansList.push_back(n2->at(ltN - l - 1));
                }
            } else if(n1->at(l) < n2->at(ltN - l - 1)){
                if(ltN - l - 1 > 0 && n1->at(l) < n2->at(ltN - l - 2)) {
                    ansList.push_back(n2->at(ltN - l - 2 ));
                } else {
                    ansList.push_back(n1->at(l));
                }
                if(l + 1 < n && n1->at(l + 1) < n2->at(ltN - l - 1)) {
                    ansList.push_back(n1->at(l + 1));
                } else {
                    ansList.push_back(n2->at(ltN - l - 1));
                }
            } else {
                return (double)(n1->at(l));
            }
        } else {
            ansList.push_back(n1->at(l));
            ansList.push_back(n2->at(ltN - l - 1));
            ansList.push_back(n1->at(r));
            ansList.push_back(n2->at(ltN - r - 1));
        }
        for(int i = 0  ;i < ansList.size() ; i++) cout << ansList[i] << ' ';
        cout << endl;
        sort(ansList.begin(),ansList.end());
        int mid = ansList.size() / 2;
        for(int i = 0  ;i < ansList.size() ; i++) cout << ansList[i] << ' ';
        cout << endl;
        if(even)
            return ((double)ansList[mid] + (double)ansList[mid - 1]) * 0.5;
        else return (double)ansList[mid];        
    }
};