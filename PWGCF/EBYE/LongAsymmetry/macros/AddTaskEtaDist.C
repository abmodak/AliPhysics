AliAnalysisTaskEtaDist* AddTaskEtaDist(const char *suffix = "")
{
    // get the manager via the static access member. since it's static, you don't need
    // to create an instance of the class here to call the function
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) {
        return 0x0;
    }
    // get the input event handler, again via a static method. 
    // this handler is part of the managing system and feeds events
    // to your task
    if (!mgr->GetInputEventHandler()) {
        return 0x0;
    }

    TString name;
    name.Form("LegCoef%s", suffix);
    // by default, a file is open for writing. here, we get the filename
    TString fileName = AliAnalysisManager::GetCommonFileName();
    fileName += ":LongFluctuations";      // create a subfolder in the file
    // now we create an instance of your task
    AliAnalysisTaskEtaDist* task = new AliAnalysisTaskEtaDist(name.Data());
    if(!task) return 0x0;
    task->SelectCollisionCandidates(AliVEvent::kINT7);
    task->SetMCRead(kFALSE);
    task->SetPileUpRead(kFALSE);
    task->SetFilterBit(96);
    task->SetChi2DoF(4);
    task->SetPtLimits(0.2, 2.0);
    task->SetEtaLimit(0.8);
    printf("Container name is %s\n",name.Data());

    // add your task to the manager
    mgr->AddTask(task);
    // your task needs input: here we connect the manager to your task
    mgr->ConnectInput(task,0,mgr->GetCommonInputContainer());
    // same for the output
    mgr->ConnectOutput(task,1,mgr->CreateContainer(name.Data(), TList::Class(), AliAnalysisManager::kOutputContainer, fileName.Data()));
    // in the end, this macro returns a pointer to your task. this will be convenient later on
    // when you will run your analysis in an analysis train on grid
    return task;
}
