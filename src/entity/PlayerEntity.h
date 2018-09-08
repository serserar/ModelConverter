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

#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

#include "DynamicEntity.h"

/**
 * @todo write docs
 */
class PlayerEntity :  DynamicEntity
{
public:
    /**
     * Default constructor
     */
    PlayerEntity();

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    PlayerEntity(const PlayerEntity& other);

    /**
     * Destructor
     */
    ~PlayerEntity();

    /**
     * @todo write docs
     *
     * @return TODO
     */
    void onInit() override;

    /**
     * @todo write docs
     *
     * @return TODO
     */
    void onAction() override;

    /**
     * @todo write docs
     *
     * @param entity TODO
     * @return TODO
     */
    void onCollision(Entity& entity) override;

    /**
     * @todo write docs
     *
     * @param status TODO
     * @return TODO
     */
    virtual void onUpdateStatus(Status2D& status);

};

#endif // PLAYERENTITY_H
