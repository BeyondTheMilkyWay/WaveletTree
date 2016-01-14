//
// Created by Domagoj Stankovic on 1/12/16.
//

#ifndef WAVELETTREE_NULLABLEOBJECT_H
#define WAVELETTREE_NULLABLEOBJECT_H

// Class representing abstract node in a tree. Can be null or an actual node.
class NullableObject {
public:
    virtual bool isNull() {
      return false;
    }
};


#endif //WAVELETTREE_NULLABLEOBJECT_H
