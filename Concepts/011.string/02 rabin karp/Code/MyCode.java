class Solution {
    public List<Integer> search(String pat, String txt) {
        int m=txt.length();
        int n=pat.length();

        int p=7;
        int mod=101;

        int txtHash=0;
        int patHash=0;
        
        int pRight=1;
        for(int i=0;i<n;i++){
            txtHash=(txtHash+((txt.charAt(i)-'a'+1)*pRight)%mod)%mod;
            patHash=(patHash+((pat.charAt(i)-'a'+1)*pRight)%mod)%mod;
            pRight=(pRight*p)%mod;
        }
        List<Integer> ans = new ArrayList<>();
        int pLeft=1;

        for(int i=0;i<=m-n;i++){
            if(txtHash==patHash){
                if(txt.substring(i,i+n).equals(pat))
                    ans.add(i);
            }

            if(i<m-n){//need to put else in 2ns statement i+n will be out of bound
                    
                txtHash=(txtHash-((txt.charAt(i)-'a'+1)*pLeft)%mod+mod)%mod;

                txtHash=(txtHash+((txt.charAt(i+n)-'a'+1)*pRight)%mod)%mod;
                patHash=(patHash*p)%mod;

                pRight=(pRight*p)%mod;
                pLeft=(pLeft*p)%mod;
            }
        }
        return ans;

    }
}
