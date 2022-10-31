
#include "LinkedList.h"
#include  "Employee.h"
//static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);
static Node* distanceNode(LinkedList* this, int nodeIndex);
static Node* getNodeWhitDistance(LinkedList* this, int nodeIndex);


/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = NULL;
	this = (LinkedList*) malloc(sizeof(LinkedList));
	if(this !=NULL)
	{
		this->pFirstNode = NULL;
		this->pLastNode = NULL;
		this->size = 0;
	}
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
	{
		returnAux = (*this).size;
	}
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */

static Node* distanceNode(LinkedList* this, int nodeIndex)
{
	int distance1;
	int distance2;
	Node* returnAux = NULL;

	if(this!=NULL && ll_len(this)>0 && nodeIndex>-1 && nodeIndex < ll_len(this))
	{
	   distance1 = nodeIndex;
	   distance2 = ll_len(this) - nodeIndex;

	   if(distance1 == distance2)
	   {
		   returnAux = this->pFirstNode;
	   }
	   else
	   {
		   if(distance1 > distance2)
		   {
			   returnAux = this->pLastNode;
		   }
		   else
		   {
			   returnAux = this->pFirstNode;
		   }
	   }
	}
	  return returnAux;
}

//**********************************************************************************
/*static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* returnAux = NULL;

    if(this!=NULL && ll_len(this)>0 && nodeIndex>-1 && nodeIndex < ll_len(this))
    {
		if(nodeIndex==0)
		{
			returnAux = this->pFirstNode;
		}
		else
		{
			returnAux = this->pFirstNode;
			for(int i=0; i<nodeIndex  ;i++)
			{
		       returnAux = (*returnAux).pNextNode;
			}
		}
    }
    return returnAux;
}*/

//************************************************************************************

static Node* getNodeWhitDistance(LinkedList* this, int nodeIndex)
{
    Node* returnAux = NULL;

    if(this!=NULL && ll_len(this)>0 && nodeIndex>-1 && nodeIndex < ll_len(this) )
    {
		if(nodeIndex==0)
		{
			returnAux = this->pFirstNode;
		}
		else
		{
			returnAux = distanceNode(this, nodeIndex);

			if(returnAux == this->pFirstNode)
			{
				for(int i=0; i<nodeIndex  ;i++)
				{
				   returnAux = (*returnAux).pNextNode;
				}
			}
			else
			{
				for(int i=ll_len(this)-1; i > nodeIndex  ;i--)
				{
					returnAux = (*returnAux).pPreviousNode;

				}
			}
		}
		}
    return returnAux;
    }


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */

static int addNode(LinkedList *this, int nodeIndex, void *pElement)// ULTIMO fantasma
{
    int returnAux = -1;
    int len;
    Node* newNode = (Node*) malloc(sizeof(Node));
    Node* pBeforeNode;

    if (this != NULL && newNode!=NULL && nodeIndex >-1 && nodeIndex <= ll_len(this))
    {
			(*newNode).pElement = pElement;
			len = ll_len(this);

			if (nodeIndex == 0) //posicion 0
			{
				(*newNode).pPreviousNode = NULL;//sin dudas
				(*newNode).pNextNode = (*this).pFirstNode;  //null o siguiente- primero se lo cargo a new lo de first
				(*this).pFirstNode = newNode; // coloco en cabecera con elemento cargado
				(*this).pLastNode = newNode;
				employee_showUnit(newNode->pElement);
			}
			else
			{
				if( nodeIndex < len)//      index 9 me traigo el 8
				{
					pBeforeNode = getNodeWhitDistance(this, nodeIndex-1);//obtengo el nodo anterior
					(*newNode).pPreviousNode = pBeforeNode;// al nuevo nodo  nodo previo le asgino la direccion del nodo anterior
					(*newNode).pNextNode = (*pBeforeNode).pNextNode;//al nuevo nodo en NextNode le asigno el mismo next node del anterior
					(*pBeforeNode).pNextNode = newNode;//al nodo anterior en el campo nextnode le asigno el nuevo nodo

				}
				else
				{

					 pBeforeNode = (*this).pLastNode;
					 (*pBeforeNode).pNextNode = newNode;
					 (*newNode).pPreviousNode = pBeforeNode;
					(*newNode).pNextNode = NULL;
					(*this).pLastNode = newNode;
					employee_showUnit(newNode->pElement);
				}
			}
			this->size++;
		returnAux = 0;
    }

    return returnAux;
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
       addNode(this,ll_len(this), pElement);
       returnAux = 0;
    }

    return returnAux;
}



void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* pNode;

    if(this != NULL)
    {
    	if(index > -1 && index < ll_len(this))
    	{
    		pNode = getNodeWhitDistance(this, index);

			if(pNode == NULL)
			{
				returnAux = NULL;
			}
			else
			{
				returnAux = (*pNode).pElement;
			}
    	}
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* pNode;

    if(this != NULL && index > -1 && index < ll_len(this))
    {
		pNode = getNodeWhitDistance(this, index);
		if(pNode != NULL)
		{
			(*pNode).pElement = pElement;
		}
		returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */

int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    int len;
    Node* pNode;
    Node* pNodeEarlier;
    Node* pNodeNext;

    if(this != NULL && index > -1 && index < ll_len(this))
    {
      len = ll_len(this);

      if(index == 0 && len == 1) // eliminar nodo 0, existiendo solo ese nodo en la lista
      {
         pNode = (*this).pFirstNode;
         (*this).pFirstNode = NULL;
         (*this).pLastNode = NULL;
         free(pNode);
         returnAux = 0;
         (*this).size--;
      }
      else
      {
    	  if(index == 0 && len > 1)// elimina nodo 0, existiendo + mas un nodo
    	  {
    		  pNode = (*this).pFirstNode;
    		  pNodeNext = (*pNode).pNextNode;
    		  (*this).pFirstNode = pNodeNext;
    		  (*pNodeNext).pPreviousNode = NULL;
    		  free(pNode);
    		  returnAux = 0;
		      (*this).size--;
    	  }
    	  else
    	  {
    		  if(index != 0 && index < len-1)// nodos intermedios
    		  {
    			  pNode = getNodeWhitDistance(this, index);
    			  pNodeEarlier = (*pNode).pPreviousNode;
    			  pNodeNext = (*pNode).pNextNode;
    			  (*pNodeEarlier).pNextNode = pNodeNext;
    			  (*pNodeNext).pPreviousNode = pNodeEarlier;
    			  free(pNode);
				  returnAux = 0;
				  (*this).size--;
    		  }
    		  else
    		  {
    			  if(index == len-1)//elimina ultimo nodo
				  {
					  pNode = (*this).pLastNode;
					  pNodeEarlier = (*pNode).pPreviousNode;
					  (*pNodeEarlier).pNextNode = NULL;
					  (*this).pLastNode = pNodeEarlier;
					  free(pNode);
					  returnAux = 0;
					  (*this).size--;
				  }

    		  }
    	  }
      }
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	for(int i = 0; i <= ll_len(this); i++)
    	{
    		if(ll_remove(this, i) == 0)
    		{
    			returnAux = 0;
    		}
    	}
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	if(ll_clear(this) == 0)
    	{
    		free(this);
    		returnAux = 0;
    	}
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	for(int i = 0; i < ll_len(this); i++)
    	{
    		if(ll_get(this, i) == pElement)
    		{
    			returnAux = i;
    			break;
    		}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	if((*this).pFirstNode != NULL)
    	{
    		returnAux = 0;
    	}
    	else
    	{
    		returnAux = 1;
    	}
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
	   if(addNode(this, index, pElement) == 0)
	   {
		   returnAux = 0;
	   }
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;

    if(this != NULL && index > -1 && index < ll_len(this))
    {
    	returnAux = ll_get(this, index);
    	ll_remove(this, index);
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	returnAux = 0;

    	for(int i = 0; i < ll_len(this); i++)
    	{
    		if(ll_get(this, i) == pElement)
    		{
    			returnAux = 1;
    			break;
    		}
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;

    if(this != NULL && this2 != NULL)
    {
    	returnAux = 0;

    	if(ll_len(this) == ll_len(this2))
    	{

			for(int i = 0; i < ll_len(this); i++)
			{
				if(ll_get(this, i) == ll_get(this2, i))
				{
					returnAux = 1;
					break;
				}
			}
    	}
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL && from > -1 && to >= from && to <= ll_len(this))
    {
       cloneArray = ll_newLinkedList();

       for(int i = from; i <= to; i++)
       {
		   ll_add(cloneArray, ll_get(this, i));
       }
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL)
        {
           cloneArray = ll_newLinkedList();

           for(int i = 0; i <= ll_len(this); i++)
           {
    		   ll_add(cloneArray, ll_get(this, i));
           }
        }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int flag = 1;
    void* pElementOne;
    void* pElementTwo;

    if(this != NULL && pFunc != NULL && (order == 0 || order == 1))
    {
    	  int newLen = ll_len(this)-1;
    	   do
    	   {
    		   flag = 0;
    		   for(int i = 0; i < newLen; i++)
    		   {
    			  pElementOne = ll_get(this, i);
				  pElementTwo = ll_get(this, i+1);

    			  if(pElementOne != NULL && pElementTwo != NULL
    				&& ((pFunc(pElementOne,pElementTwo) > 0 && order == 1)
					|| (pFunc(pElementOne,pElementTwo) < 0 && order == 0)))
    			  {
					  ll_set(this, i, pElementTwo);
					  ll_set(this, i+1, pElementOne);
					  flag = 1;
    			  }
    		   }
    		   newLen--;
    	   }while(flag == 1);
    	   returnAux =0;
    }

    return returnAux;

}


/// ------------------------------------------------------------------------

int ll_map(LinkedList* this, int (*pFunc)(void*))
{
	int retorno = -1;
    void* pElement;

	if(this != NULL && pFunc != NULL)
	{
		for(int i = 0; i < ll_len(this); i++)
		{
			pElement = ll_get(this, i);
			pFunc(pElement);
			retorno = 0;
		}
	}
	return retorno;
}

LinkedList* ll_filter(LinkedList* this,  int (*pFunc)(void*))
{
    LinkedList* newList = NULL;
    void* pElement;

    newList= ll_newLinkedList(); // creo lista nueva
    if(this != NULL && pFunc != NULL && newList !=NULL)
    {
		for(int i = 0; i < ll_len(this); i++)
		{
			pElement = ll_get(this, i);
			if(pFunc(pElement) == 0)
			{
				ll_add(newList,pElement);// lista  limpia

			}

		}

    }
    return newList;
}
