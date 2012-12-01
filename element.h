/**
 * \file   element.h
 *
 * \author Maria Levshinovskaya <masa.levs@gmail.com>
 * 
 * \brief
 *
 *
 */
#ifndef __ELEMENT_H
#define __ELEMENT_H

#include <QString>

class Element
{
  int      id;
  QString  name;
  QString  description;
  QString  category;
  unsigned box;
  unsigned row;
  unsigned column;
  int      count;
  QString  link;
  QString  price;
  QString  comment;

public:
  Element(QString name) {
    this->name = name;
  }
  ~Element() {}

  QString getName() {
    return name;
  }
  QString getDescription() {
    return description;
  }
  QString getCategory() {
    return category;
  }
  unsigned getBox() {
    return box;
  }
  unsigned getRow() {
    return row;
  }
  unsigned getColumn() {
    return column;
  }
  int getCount() {
    return count;
  }
  QString getLink() {
    return link;
  }
  QString getPrice() {
    return price;
  }
  QString getComment() {
    return comment;
  }

  bool setName(QString newName) {
    name = newName;
    return true;
  }
  bool setDescription(QString newDescription) {
    description = newDescription;
    return true;
  }
  bool setCategory(QString newCategory) {
    category = newCategory;
    return true;
  }
  bool setBox(unsigned newBox) {
    box = newBox;
    return true;
  }
  bool setRow(unsigned newRow) {
    row = newRow;
    return true;
  }
  bool setColumn(unsigned newColumn) {
    column = newColumn;
    return true;
  }
  bool setCount(int newCount) {
    count = newCount;
    return true;
  }
  bool setLink(QString newLink) {
    link = newLink;
    return true;
  }
  bool setPrice(QString newPrice) {
    price = newPrice;
    return true;
  }
  bool setComment(QString newComment) {
    comment = newComment;
    return true;
  }
};

#endif /* __ELEMENT_H */

