/****************************************************************************
 *
 * fkie_message_filters
 * Copyright © 2018 Fraunhofer FKIE
 * Author: Timo Röhling
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ****************************************************************************/
#ifndef INCLUDE_FKIE_MESSAGE_FILTERS_SELECTOR_H_
#define INCLUDE_FKIE_MESSAGE_FILTERS_SELECTOR_H_

#include "filter.h"

namespace fkie_message_filters
{

#ifndef DOXYGEN
template<class IO, std::size_t... Is>
class Selector;
#endif

/** \brief Choose an arbitrary set of inputs to be forwarded
 *
 * Sometimes, a filter pipeline that processes multiple inputs together, must be split up to handle those inputs
 * independently. The selector class can pick an arbitrary set of the inputs and forward it.
 * \code
 * namespace mf = fkie_message_filters;
 *
 * using BufferIn = mf::Buffer<T0, T1, T2>;
 * using Select = mf::Selector<BufferIn::Output, 1, 0>;
 * using BufferOut = mf::Buffer<T1, T0>;
 *
 * BufferIn buf_in;
 * Select select;
 * BufferOut buf_out;
 * mf::chain(buf_in, select, buf_out);
 * \endcode
 * \sa Divider, Combiner
 */
#ifndef DOXYGEN
template<class... Inputs, std::size_t... Is>
class Selector<IO<Inputs...>, Is...> : public Filter<IO<Inputs...>, typename IO<Inputs...>::template Select<Is...>>
#else
template<class... Inputs, std::size_t... Is>
class Selector : public Filter<IO<Inputs...>, typename IO<Inputs...>::template Select<Is...>>
#endif
{
protected:
    void receive(const Inputs&... in) override;
};

} // namespace fkie_message_filters

#include "selector_impl.h"

#endif /* INCLUDE_FKIE_MESSAGE_FILTERS_SELECTOR_H_ */
