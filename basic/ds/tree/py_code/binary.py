#AVL Tree

n=[10,18,7,1,16,5,17,4,2,14,13,6,12,15,3,9,8,11,19,20]
d=[2,1,12,18,11,7,16,5]

class tree_node:
    def __init__(self, value):
        self.value=value
        self.right=None
        self.left=None
        self.height=0
    def __str__(self) -> str:
        return "l:{} v:{} h:{} r:{}".format(self.left, self.value, self.height, self.right)

class tree:
    def __init__(self):
        self.root=None
    def _insert(self, curr_node, val):
        if not curr_node:
           return 
        if curr_node.value > val:
            #print("lt:", curr_node)
            if curr_node.left:
                self._insert(curr_node.left, val)
            else:
                curr_node.left=tree_node(val)
        else:
            #print("rt:", curr_node)
            if curr_node.right:
                self._insert(curr_node.right, val)
            else:
                curr_node.right=tree_node(val)
    def insert(self, val):
        if self.root == None:
            self.root=tree_node(val)
            #print("ro:", self.root)
        else:
           self._insert(self.root, val) 
    def _delete(self, curr_node, val):
        if curr_node == None:
            return curr_node
        if curr_node.value > val:
            curr_node.left = self._delete(curr_node.left, val)
            return curr_node
        elif curr_node.value < val:
            curr_node.right = self._delete(curr_node.right, val)
            return curr_node
        #found node
        if curr_node.left == None:
            if curr_node.right == None:
                #Found a lone leaf node. Delete it and return None.
                del(curr_node)
                return None
        if curr_node.left == None:
            #Node with no left side but only right side.
            #return the right node and delete the current node
            t=curr_node.right
            del(curr_node)
            return t
        if curr_node.right == None:
            #No right side only left side.
            t=curr_node.left
            del(curr_node)
            return t
        #handle node with both left and right 
        #Start with left side. Find the largest value on the left side.
        #Inorder predecessor. Largest value from the left side.
        succParent = curr_node
        succ = curr_node.left 
        while succ.right:
            succParent = succ 
            succ = succ.right
        curr_node.value = succ.value
        if succParent == curr_node:
            succParent.left=succ.left
        else:
            succParent.right=succ.left
        del(succ)
        return curr_node
    def delete(self, val):
        if self.root == None:
            return
        self._delete(self.root, val)
    def _display_aux(self, node):
        """Returns list of strings, width, height, and horizontal coordinate of the root."""
        # No child.
        if node.right is None and node.left is None:
            line = '%s' % node.value
            width = len(line)
            height = 1
            middle = width // 2
            return [line], width, height, middle
        # Only left child.
        if node.right is None:
            lines, n, p, x = self._display_aux(node.left)
            s = '%s' % node.value
            u = len(s)
            first_line = (x + 1) * ' ' + (n - x - 1) * '_' + s
            second_line = x * ' ' + '/' + (n - x - 1 + u) * ' '
            shifted_lines = [line + u * ' ' for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, n + u // 2
        # Only right child.
        if node.left is None:
            lines, n, p, x = self._display_aux(node.right)
            s = '%s' % node.value
            u = len(s)
            first_line = s + x * '_' + (n - x) * ' '
            second_line = (u + x) * ' ' + '\\' + (n - x - 1) * ' '
            shifted_lines = [u * ' ' + line for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, u // 2
        # Two children.
        left, n, p, x = self._display_aux(node.left)
        right, m, q, y = self._display_aux(node.right)
        s = '%s' % node.value
        u = len(s)
        first_line = (x + 1) * ' ' + (n - x - 1) * '_' + s + y * '_' + (m - y) * ' '
        second_line = x * ' ' + '/' + (n - x - 1 + u + y) * ' ' + '\\' + (m - y - 1) * ' '
        if p < q:
            left += [n * ' '] * (q - p)
        elif q < p:
            right += [m * ' '] * (p - q)
        zipped_lines = zip(left, right)
        lines = [first_line, second_line] + [a + u * ' ' + b for a, b in zipped_lines]
        return lines, n + m + u, max(p, q) + 2, n + u // 2
    def print_tree(self):
        if self.root:
            lines, *_ = self._display_aux(self.root)
            for line in lines:
                print(line)

if __name__ == "__main__":
    t = tree()
    for i in range(0, len(n)):
        t.insert(n[i])
    t.print_tree()
    for i in range(0, len(d)):
        print("after del ", d[i])
        t.delete(d[i])
        t.print_tree()