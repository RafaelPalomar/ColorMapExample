#include <vtkSmartPointer.h>
#include <vtkHausdorffDistancePointSetFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkPointData.h>

int main(int argc, char *argv[])
{
  
  vtkSmartPointer<vtkCubeSource> cubeSource =
    vtkSmartPointer<vtkCubeSource>::New();
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
   
  vtkSmartPointer<vtkHausdorffDistancePointSetFilter> distanceFilter =
    vtkSmartPointer<vtkHausdorffDistancePointSetFilter>::New();
  
  distanceFilter->SetInputConnection(1, cubeSource->GetOutputPort());
  distanceFilter->SetInputConnection(0, sphereSource->GetOutputPort());
  distanceFilter->Update();
  
  distanceFilter->GetOutput(0)->GetPointData()->SetScalars(distanceFilter->GetOutput()->GetPointData()->GetArray(0));

  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
  
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(distanceFilter->GetOutputPort(0));
  sphereMapper->ScalarVisibilityOn();

  vtkSmartPointer<vtkActor> cubeActor =
    vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);
  cubeActor->GetProperty()->SetRepresentationToWireframe();

  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
    
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(cubeActor);
  renderer->AddActor(sphereActor);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renderWindow);
  
  renderWindow->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
