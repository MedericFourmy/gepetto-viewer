#include <gepetto/viewer/roadmap-viewer.h>
#include <sstream>
#include <gepetto/viewer/leaf-node-xyzaxis.h>
#include <gepetto/viewer/leaf-node-line.h>

namespace graphics {
    /* Declaration of private function members */

    RoadmapViewer::RoadmapViewer (const std::string& name,const osgVector4& colorNode,float radiusSphere,float sizeAxis,const osgVector4& colorEdge):
        graphics::Node (name), list_nodes_(),list_edges_()
    {
        colorNode_=osgVector4(colorNode);
        colorEdge_=osgVector4(colorEdge);
        radiusSphere_=radiusSphere;
        sizeAxis_ = sizeAxis_;

    }

    RoadmapViewer::RoadmapViewer (const RoadmapViewer& other):
        graphics::Node (other)
    {
       /*size_t i;
        for (i=0;i < other.getNumOfChildren(); i++)
        {
            addChild(other.getChild(i));
        }*/
        //TODO
    }

    void RoadmapViewer::initWeakPtr(RoadmapViewerWeakPtr other_weak_ptr)
    {
        weak_ptr_ = other_weak_ptr;
    }

    /* End of declaration of private function members */

    /* Declaration of public function members */
    RoadmapViewerPtr_t RoadmapViewer::create(const std::string& name,const osgVector4& colorNode,float radiusSphere,float sizeAxis,const osgVector4& colorEdge)
    {
        RoadmapViewerPtr_t shared_ptr(new RoadmapViewer(name,colorNode,radiusSphere,sizeAxis,colorEdge));

        // Add reference to itself
        shared_ptr->initWeakPtr(shared_ptr);

        return shared_ptr;
    }

   RoadmapViewerPtr_t RoadmapViewer::createCopy(RoadmapViewerPtr_t other)
    {
        RoadmapViewerPtr_t shared_ptr(new RoadmapViewer(*other));

        // Add reference to itself
        shared_ptr->initWeakPtr(shared_ptr);

        return shared_ptr;
    }


   /*RoadmapViewerPtr_t RoadmapViewer::clone(void) const
   {
       return RoadmapViewer::createCopy(weak_ptr_.lock());
   }*/

   RoadmapViewerPtr_t RoadmapViewer::self(void) const
   {
       return weak_ptr_.lock();
   }

   // -------------------------------------------

   bool RoadmapViewer::addNode(osgVector3 position, osgQuat quat){
       std::stringstream msg;
       msg << getID()<<"_node"<<list_nodes_.size();
       LeafNodeXYZAxisPtr_t node = LeafNodeXYZAxis::create(msg.str(),colorNode_,radiusSphere_,sizeAxis_);
       node->applyConfiguration (position,quat);

       list_nodes_.push_back(node);
       this->asQueue()->addChild(node->asGroup());

       return true;
   }

   bool RoadmapViewer::addEdge(osgVector3 from, osgVector3 to){
       std::stringstream msg;
       msg << getID()<<"_Edge"<<list_edges_.size();
       LeafNodeLinePtr_t edge = LeafNodeLine::create (msg.str(),from, to, colorEdge_);

       list_edges_.push_back(edge);
       this->asQueue()->addChild(edge->asGroup());
       return true;
   }

   void RoadmapViewer::removeAllChildren()
   {
       list_nodes_.clear();
       list_edges_.clear();
       this->asQueue()->removeChild(0, this->asQueue()->getNumChildren());
   }

   void RoadmapViewer::setVisibilityMode (const VisibilityMode& visibility_state)
   {
       Node::setVisibilityMode (visibility_state);
       std::list<graphics::NodePtr_t>::iterator iter_list_of_objects;
       for (iter_list_of_objects = list_nodes_.begin();
            iter_list_of_objects != list_nodes_.end();
            iter_list_of_objects++)
       {
           (*iter_list_of_objects)->setVisibilityMode ( visibility_state );
       }
       for (iter_list_of_objects = list_edges_.begin();
            iter_list_of_objects != list_edges_.end();
            iter_list_of_objects++)
       {
           (*iter_list_of_objects)->setVisibilityMode ( visibility_state );
       }
   }

   void RoadmapViewer::setLightingMode (const LightingMode& lighting_state)
   {
       Node::setLightingMode ( lighting_state );
       ::std::list<NodePtr_t>::iterator iter_list_of_objects;
       for (iter_list_of_objects = list_nodes_.begin();
            iter_list_of_objects != list_nodes_.end();
            iter_list_of_objects++)
       {
           (*iter_list_of_objects)->setLightingMode ( lighting_state );
       }
       for (iter_list_of_objects = list_edges_.begin();
            iter_list_of_objects != list_edges_.end();
            iter_list_of_objects++)
       {
           (*iter_list_of_objects)->setLightingMode ( lighting_state );
       }
   }

   void RoadmapViewer::setWireFrameMode (const WireFrameMode& wireframe_state)
   {
       Node::setWireFrameMode ( wireframe_state );

       ::std::list<NodePtr_t>::iterator iter_list_of_objects;
       for (iter_list_of_objects = list_nodes_.begin();
            iter_list_of_objects != list_nodes_.end();
            iter_list_of_objects++)
       {
           (*iter_list_of_objects)->setWireFrameMode ( wireframe_state );
       }
       for (iter_list_of_objects = list_edges_.begin();
            iter_list_of_objects != list_edges_.end();
            iter_list_of_objects++)
       {
           (*iter_list_of_objects)->setWireFrameMode ( wireframe_state );
       }
   }


    /* End of declaration of public function members */


} // namespace graphics
