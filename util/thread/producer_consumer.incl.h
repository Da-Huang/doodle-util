#include "producer_consumer.h"

#include <thread>

namespace util {

template <typename ResourceType>
ProducerConsumer<ResourceType>::~ProducerConsumer() {
  Join();
  for (std::thread* producer : producers_) {
    delete producer;
  }
  for (std::thread* consumer : consumers_) {
    delete consumer;
  }
}

template <typename ResourceType>
template <typename Function>
void ProducerConsumer<ResourceType>::AddProducer(Function&& produce) {
  producers_.push_back(new std::thread(produce, &queue_));
}

template <typename ResourceType>
template <typename Function>
void ProducerConsumer<ResourceType>::AddConsumer(Function&& consume) {
  consumers_.push_back(new std::thread([this, consume] {
    ResourceType resource;
    while (queue_.Pop(&resource)) {
      consume(resource);
    }
  }));
}

template <typename ResourceType>
void ProducerConsumer<ResourceType>::Join() {
  for (std::thread* producer : producers_) {
    if (producer->joinable()) {
      producer->join();
    }
  }
  for (std::thread* consumer : consumers_) {
    if (consumer->joinable()) {
      consumer->join();
    }
  }
}

}  // namespace util
