#include "Agent.h"

bool QueueEntry::operator<(const QueueEntry& rhs) const { 
	if (this->weight >= rhs.weight)
    return true;
  else
    return false;

}