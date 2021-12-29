/*
Convert a non-negative integer num to its English words representation.

 

Example 1:

Input: num = 123
Output: "One Hundred Twenty Three"
Example 2:

Input: num = 12345
Output: "Twelve Thousand Three Hundred Forty Five"
Example 3:

Input: num = 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Example 4:

Input: num = 1234567891
Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"
*/

class Solution {
public:
    string numberToWords(int num) {
        vector<string> high_order = {"Thousand","Million","Billion"};
        string res = convertHundred(num%1000);
        int i = 0;
        while ( num )
        {
            num /= 1000;
            res = num % 1000 ? convertHundred(num % 1000) + " " + high_order[i] + " " + res: res;
            i++;
        }
        
        while ( res.back() == ' ')
            res.pop_back();
    
        return res.empty() ? "Zero" : res;
    }
    
    string convertHundred(int num)
    {
        vector<string> LessthanTwenty = {"","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen", "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"};
        vector<string> TwentyToNinty = {"","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"};
        string res;
        int h = num / 100, t = num % 100, o = num % 10;
        res = t < 20 ? LessthanTwenty[t] : TwentyToNinty[t/10] + (o?" "+LessthanTwenty[o] : "");
        if ( h > 0 ) 
            res = LessthanTwenty[h] + " Hundred" + (t ? " " + res: "");
        return res;
    }
};