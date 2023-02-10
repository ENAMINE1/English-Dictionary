// Traverse the child nodes
                temp = temp->child;
                // If current character is not present as sibling
                while (temp->sibling != NULL)
                {
                    // If current character is present as sibling
                    if (temp->sibling->alphabet >= word[i])
                        break;
                    // Else traverse the sibling nodes
                    temp = temp->sibling;
                }
                // If current character is not present as sibling
                if (temp->sibling->alphabet != word[i])
                {
                    // Create a new node and make it sibling of last child
                    struct node *temp1 = newNode(word[i]);
                    temp1->sibling = temp->sibling;
                    temp->sibling = temp1;
                    temp = temp->sibling;
                }