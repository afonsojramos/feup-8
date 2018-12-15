<span class="list-group-item flex-column align-items-start rounded mb-2 pt-3 pl-4">
    <div class="d-flex w-100 justify-content-between">
        <h4 class="mb-1">{{ $test->title }}</h4>
    </div>
    <div class="test-description w-100 justify-content-between">
        <h5 class="mb-1 w-100"><br><pre>{{ $test->test_code }}</pre></h5>
        @if(Auth::check() && $exercise->creator_id == Auth::user()->id)
        <div id="edit-buttons">
            <button id="edit-button" class="btn btn-secondary btn-xs rounded" style="margin-right: 2%" data-toggle="modal" data-target=".edit-test-modal_{{ $test->id }}">
                <i class="fas fa-pen"></i>
            </button>
            <form method="POST" action="{{ action('Web\TestController@removeTest', ['id' => $exercise->id,'test_id' => $test->id]) }}">
            {{ csrf_field() }}
                <button type="submit" id="remove-button" class="btn btn-danger btn-xs rounded">
                    <i class="fas fa-trash-alt"></i>
                </button>
            </form>
        </div>
        @endif
        <div class="d-flex w-100 justify-content-between">
            <h6 class="mb-1 w-75" style="font-style: italic; color: cadetblue;">{{ $test->hint }}</h6>
            @if(Auth::check() && $exercise->creator_id == Auth::user()->id) 
            <button id="hint-button" class="btn btn-secondary btn-xs rounded" data-toggle="collapse" data-target=".test_{{ $test->id }}">
                @if ($test->hint!=null)
                    <i class="fa fa-pen"></i> Edit hint
                @else 
                    Add Hint
                @endif   
            </button>
            @endif
        </div>
    </div>
    <div class="test_{{ $test->id }} collapse ontainer col-12 flex-column align-items-start rounded mb-2 pt-3">
        <div class="content">
            <div>
                <form method="POST" action="{{ action('Web\TestController@addTipToExercise', ['id' => $exercise->id,'test_id' => $test->id]) }}"
                    enctype="multipart/form-data" id={{ "form" . $test->id  }} class="form-hint">
                    @csrf
                    <div class="row col-12">
                        <input type="hidden" name="testID" value={{ $test->id }}>
                        <textarea class="col-12 rounded" name="form-hint" style="overflow:hidden;" placeholder="Enter the hint here" maxlength="200" rows="2" wrap="hard">{{ $test->hint }}</textarea>
                    </div>
                    <div class="row justify-content-end pr-5">
                        <button class="hint-submit btn btn-primary rounded" style=" margin-left: 0; margin-top: 0.5rem;" type="submit"><i class="fa fa-share"></i> Save hint</button>
                    </div>
                </div>
                </form>
            </div>
        </div>
    </div>
    <div class="edit-test-modal_{{ $test->id }} modal fade" tabindex="-1" role="dialog" aria-labelledby="editModal" aria-hidden="true" data-backdrop="false" style="display: none" aria-hidden="true">
        <div class="modal-dialog modal-lg">
            <div class="modal-content">
                <div class="modal-header">
                    <h4 class="modal-title">Edit Test {{ $test->title }} Code </h4>
                    <button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>
                </div>
                <div class="modal-body">
                    <div class="card-body">
                        <form method="POST" action="{{ action('Web\TestController@editTestCode', ['id' => $exercise->id,'test_id' => $test->id]) }}"
                            enctype="multipart/form-data">
                            @csrf
                            <div class="form-group row col-md-12">
                                <label for="title" class="col-sm-2 col-form-label text-md-right">{{ __('Test Title') }}</label>
                                <div class="col-md-10">
                                <input id="title" type="text" class="rounded form-control{{ $errors->has('email') ? ' is-invalid' : '' }}" name="form-title" value="{{$test->title}}" required autofocus>
                                    @if ($errors->any())
                                        <span class="invalid-feedback" role="alert">
                                            <strong>{{ $errors->first() }}</strong>
                                        </span>
                                    @endif
                                </div>
                            </div>
                            <div class="form-group row col-md-12">
                                <label for="test-code" class="col-sm-2 col-form-label text-md-right">
                                    {{__('Code of Test')}}
                                </label>
                                <div class="col-md-10">
                                    <textarea class="w-100 col-md-12 rounded form-control{{ $errors->has('test-code') ? ' is-invalid' : '' }}"
                                        id="test-code" cols="30" rows="5" name="form-test-code" wrap="hard"
                                        style="font-family: monospace;"
                                        required autofocus>{{ $test->test_code }}</textarea>
                                    @if ($errors->any())
                                    <span class="invalid-feedback" role="alert">
                                        <strong>{{ $errors->first() }}</strong>
                                    </span>
                                    @endif
                                </div>
                            </div>
                            <div class="form-group row mb-0">
                                <div class="col-md-8 offset-md-4">
                                    <button type="submit" class="btn btn-primary">
                                        {{ __('Save Changes') }}
                                    </button>
                                </div>
                            </div>
                        </form>
                    </div>
                </div>
            </div>
        </div>
    </div>
</span>