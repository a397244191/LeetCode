/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode* nul = NULL;
        stack<pair<TreeNode*,bool>> s;
        s.push(make_pair(root,false));
        pair<TreeNode*,bool> use;
        TreeNode *swap1 = NULL,*swap2 = NULL;
        TreeNode* last = NULL;
        while(!s.empty()){
            use = s.top();
            s.pop();
            if(use.first == NULL) continue;
            if(!use.second){
                s.push(make_pair(use.first->right,false));
                s.push(make_pair(use.first,true));
                s.push(make_pair(use.first->left,false));
                continue;
            }
            if(last != NULL && last->val > use.first->val) {
                if(swap1 ==NULL)swap1 = last;
                swap2 = use.first;
            }            
            last = use.first;
            
        }
        swap(swap1->val,swap2->val);
    }
};
