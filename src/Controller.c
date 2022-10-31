/*
 * Controller.c
 *
 *  Created on: 15 dic. 2021
 *      Author: stanc
 */

#include "Controller.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pFile;

	pFile = fopen(path, "r");

	if(pFile != NULL)
	{
		if(parser_EmployeeFromText(pFile, pArrayListEmployee) == 0)
		{
			retorno = 0;
		}
	}

    fclose(pFile);

    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;

	FILE* pFile  = fopen(path, "r");

	if(pFile != NULL)
	{
		if(parser_EmployeeFromBinary(pFile, pArrayListEmployee) == 0)
		{
			retorno = 0;
			fclose(pFile);
		}
		else
		{
			puts("\n fallo parser");
		}
	}


    return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int id;
	Employee* pNewEmployee;

    if(pArrayListEmployee != NULL)
    {
    	if(controller_maxId(pArrayListEmployee, &id) == 0)
    	{
    		pNewEmployee = employee_new();
    		id++;

    		if(employee_register(pNewEmployee, id) == 0)
    		{
    			ll_add(pArrayListEmployee, pNewEmployee);
    			retorno = 0;
    		}

    	}

    }

	return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int idIngresado;
    int id;
    int flagEncontrado = 0;
	Employee* pBufferEmployee;

	if(pArrayListEmployee != NULL)
	{
		controller_ListEmployee(pArrayListEmployee);
		if(utn_getNumber(&idIngresado, "\n »» SELECCIONE UN EMPLEADO MEDIANTE ID:  "
						,"\n × ERROR. REINGRESE EL ID.\n",0,2000, 1) == 0)
		{
			for(int i = 0; i < ll_len(pArrayListEmployee); i++)
			{
				pBufferEmployee = ll_get(pArrayListEmployee, i);
				employee_getId(pBufferEmployee, &id);

				if(id == idIngresado)
				{
				   flagEncontrado = 1;
                   employee_posterSelected();
                   employee_showUnit(pBufferEmployee);
                   if(employee_modify(pBufferEmployee) != 0)
                   {
                	   printf("\n »» NO SE HAN REALIZADO CAMBIOS");
                   }
                   retorno = 0;
                   break;
				}
			}

			if(flagEncontrado != 1)
			{
				printf("\n ×× EL ID INGRESADO ES INEXISTENTE. ");
			}
		}
	}
	return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int id;
	int idIngresado;
	Employee* pEmpleado;

	if(pArrayListEmployee != NULL)
	{
      if(employee_showList(pArrayListEmployee) == 0)
      {
    	  if(utn_getNumber(&idIngresado,"\n » INGRESE EL ID DEL EMPLEADO:", "\n <> ERROR.", 0, 1000,1) == 0)
    	  {
    		  for(int i = 0; i <= ll_len(pArrayListEmployee); i++)
    		  {
    			  pEmpleado = ll_get(pArrayListEmployee, i);
    			  employee_getId(pEmpleado, &id);
                  if(id == idIngresado)
                  {
                      ll_remove(pArrayListEmployee, i);
                	  retorno = 0;
                	  break;
                  }
    		  }
    	  }
      }
	}

	return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;

	if(pArrayListEmployee != NULL)
	{
		if(employee_showList(pArrayListEmployee) == 0)
		{
			retorno = 0;
		}
	}

    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int orden;
	int criterio;

	if(pArrayListEmployee != NULL)
	{
		criterio = employee_menuSortStandard();
		if(criterio != 5)
		{
		   orden = employee_menuSortWay();
			if(orden == 2)
			{
				orden = 0;
			}
		}

			switch(criterio)
			{
				case 1:
					ll_sort(pArrayListEmployee, employee_sortId, orden);
					retorno = 0;
					break;
				case 2:
					ll_sort(pArrayListEmployee, employee_sortNames, orden);
					retorno = 0;
					break;
				case 3:
					ll_sort(pArrayListEmployee, employee_sortHours, orden);
					retorno = 0;
					break;
				case 4:
					ll_sort(pArrayListEmployee, employee_sortSalary, orden);
					retorno = 0;
					break;
				case 5:
					printf("\n »» Saliendo...");
					retorno = 0;
					break;
			}
	}

    return retorno;
}
/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int id;
	char nombre[128];
	int horasT;
	int salario;
	Employee* pBufferEmp;

	if(path != NULL && pArrayListEmployee != NULL)
	{
		FILE* pFile;

		pFile = fopen(path, "w");

		if(pFile != NULL)
		{
			fprintf(pFile, " ID, NOMBRE, HORAS TRABAJADAS, SUELDO\n");
			for(int i = 0; i < ll_len(pArrayListEmployee); i++)
			{
				pBufferEmp = ll_get(pArrayListEmployee, i);
				employee_getId(pBufferEmp, &id);
				employee_getNombre(pBufferEmp, nombre);
				employee_getHorasTrabajadas(pBufferEmp, &horasT);
				employee_getSueldo(pBufferEmp, &salario);
				fprintf(pFile, "%d, %s, %d, %d\n", id,nombre,horasT, salario);
				retorno =0;
			}

		}

		fclose(pFile);
	}

    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
	Employee* pBufferEmp;

	if(path != NULL && pArrayListEmployee != NULL)
	{
		FILE* pFile = fopen(path, "w");
		if(pFile != NULL)
		{

			for(int i = 0; i < ll_len(pArrayListEmployee); i++)
			{
				pBufferEmp = ll_get(pArrayListEmployee, i);
				fwrite(pBufferEmp,sizeof(Employee),1, pFile);
				retorno =0;
			}
		}

		fclose(pFile);
	}

    return retorno;
}

int controller_maxId(LinkedList* pArrayListEmployee, int* id)
{
	int retorno = -1;
	int maxId = 0;
	int flag = 0;
	int idEmp;
	Employee* pEmpleado;

	if(pArrayListEmployee != NULL)
	{
		for(int i = 0; i < ll_len(pArrayListEmployee); i++)
	    {
			pEmpleado = ll_get(pArrayListEmployee, i);
		    employee_getId(pEmpleado, &idEmp);
		    if(flag == 0 ||idEmp > maxId)
		    {
		    	maxId = idEmp;
		    	flag = 1;
		    	retorno = 0;
		    }
		}
		*id = maxId;
	}

	return retorno;
}
