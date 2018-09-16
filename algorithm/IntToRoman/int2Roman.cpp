class Solution {
public:
    string intToRoman(int num) {
        string outputstr("M CM D CD C XC L XL X IX V IV I");
        istringstream iss(outputstr);
        string token;
        vector<string> str;
        int arr[13] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
        while(getline(iss, token, ' ')) {
            str.push_back(token);
        }
        string output;
        int use = 0;
        while(num && use < 13) {
            if(num - arr[use] >= 0) {
                output += str[use];
                num -= arr[use];
            } 
            else use++;
        }
        return output;
    }
};