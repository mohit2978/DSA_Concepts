# Notes
![alt text](<010flatten bt and bt to dll_240401_000940.jpg>)
![alt text](<010flatten bt and bt to dll_240401_000940(1).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(2).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(3).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(4).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(5).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(6).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(7).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(8).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(9).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(10).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(11).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(12).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(13).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(14).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(15).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(16).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(17).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(18).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(19).jpg>)



![alt text](<010flatten bt and bt to dll_240401_000940(20).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(21).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(22).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(23).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(24).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(25).jpg>)



```java

class MyHashMap {
    private int size;
    private LinkedList<HMNode>[] bucket;
    private class HMNode{
        int key;
        int val;
        HMNode(int key,int val){
            this.key=key;
            this.val=val;
        }
    }

    private void initBucket(int k){
        bucket=new LinkedList[k];
        for(int i=0;i<k;i++){
            bucket[i]=new LinkedList<>();
        }
    }
    public MyHashMap() {
        size=0;
        initBucket(4);
    }
    private int getWithInLL(int key,int i){
        int res=0;
        for(HMNode node:bucket[i]){
            if(node.key==key) return res;
            res++;
        }
        return -1;
    }
    private void rehash(){
        LinkedList<HMNode>[] oldBucket=bucket;
        initBucket(oldBucket.length*2);
        this.size=0;
        for(int i=0;i<oldBucket.length;i++){
            for(var node:oldBucket[i]){
                put(node.key,node.val);
            }
        }
    }
    public void put(int key, int value) {
        int idx=key%bucket.length;
        int llidx=getWithInLL(key,idx);
        if(llidx!=-1){
            bucket[idx].get(llidx).val=value;
        }else{
            bucket[idx].add(new HMNode(key,value));
            size++;
        }
        double lambda=size*1.0/bucket.length;
        if(lambda>2.0) rehash();
    }
    
    public int get(int key) {
        int idx=key%bucket.length;
        int llidx=getWithInLL(key,idx);
        if(llidx!=-1){
            return bucket[idx].get(llidx).val;
        }else{
           return -1;
        }
    }
    
    public void remove(int key) {
        int idx=key%bucket.length;
        int llidx=getWithInLL(key,idx);
        if(llidx!=-1){
            bucket[idx].remove(llidx);
            size--;
        }
    }
}

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap obj = new MyHashMap();
 * obj.put(key,value);
 * int param_2 = obj.get(key);
 * obj.remove(key);
 */
```



