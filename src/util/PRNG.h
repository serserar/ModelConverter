/*
 * Copyright 2018 <copyright holder> <email>
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
 */

#ifndef PRNG_H
#define PRNG_H
#include <random>
#include <algorithm>
#include <chrono>
/**
 * @todo write docs
 */
class PRNG
{
public:
	PRNG()
	: m_Gen( std::random_device()() )
	, m_Dis( 0.0f, 1.0f )
	{
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		// prepare PRNG
		m_Gen.seed(seed);
	}

	explicit PRNG( uint32_t seed )
	: m_Gen( seed )
	, m_Dis( 0.0f, 1.0f )
	{
	}

	float RandomFloat()
	{
		return static_cast<float>( m_Dis( m_Gen ) );
	}

	int RandomInt( int Max )
	{
		std::uniform_int_distribution<> DisInt( 0, Max );
		return DisInt( m_Gen );
	}

private:
	std::mt19937 m_Gen;
	std::uniform_real_distribution<float> m_Dis;

};

#endif // PRNG_H
