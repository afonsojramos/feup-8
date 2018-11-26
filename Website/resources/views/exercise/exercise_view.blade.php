@extends('layouts.app')

@section('title', $exercise->title)

@section('content')
<div>
    <div class="list-group container">
        <div class="d-flex w-100 justify-content-between">
            <h3 class="mb-1">{{ $exercise->title }}</h3>
            <p class="mb-1">{{ $exercise->creator_name }}</p>
        </div>
        <div class="edition d-flex w-100 justify-content-between rounded mb-2 pt-3 pl-4">
            <h5 class="mb-1" style="white-space: pre-line;">{{ $exercise->description }}</h5>
            <div id="edit-description-button" class="btn btn-danger btn-xs rounded"
                data-toggle="modal" data-target="#edit-modal"><img src="/images/edit.png" alt="edit" height="20" width="20"></div>
        </div>
        <div id="edit-modal" class="modal fade" aria-hidden="true">
            <div class="modal-dialog modal-lg">
                <div class="modal-content">
                    <div class="modal-header">
                        <h4 class="modal-title">Edit Exercise '{{ $exercise->title }}' Description</h4>
                        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>
                    </div>
                    <div class="modal-body">
                        <div class="card-body">
                            <form method="POST" action="{{ action('Web\ExerciseController@editExercise', ['id' => $exercise->id]) }}"
                                enctype="multipart/form-data">
                                @csrf
                                <div class="form-group row">
                                    <label for="description" class="col-sm-4 col-form-label text-md-right">
                                        {{__('Description')}}
                                    </label>
                                    <div class="col-md-6">

                                        <textarea class="rounded form-control{{ $errors->has('description') ? ' is-invalid' : '' }}"
                                            id="description" cols="5" rows="3" name="form-description" wrap="hard"
                                            required autofocus>{{ $exercise->description }}</textarea>

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
    </div>
    <hr class="my-4 w-75">
    <div class="list-group container">
        <div>
            <button class="rounded btn-primary w-100" style="margin-bottom: 2%;" data-toggle="collapse" data-target="#newTest">
                Add a New Test </button>
            <div id="newTest" class="collapse list-group-item list-group-item-action flex-column align-items-start rounded mb-2 pt-3 pl-4"
                style="margin-bottom: 2%;">
                <form method="POST" action="{{ action('Web\TestController@addTestToExercise', ['id' => $exercise->id]) }}"
                    enctype="multipart/form-data">
                    @csrf
                    <div class="form-group row">
                        <label for="title" class="col-sm-12 col-form-label text-md-left">{{ __('Test Title') }}</label>
                        <div class="col-md-12">
                            <input id="title" type="text" class="form-control{{ $errors->has('title') ? ' is-invalid' : '' }}" name="form-title" value="{{ old('title') }}" required autofocus>
                            @if ($errors->any())
                                <span class="invalid-feedback" role="alert">
                                    <strong>{{ $errors->first() }}</strong>
                                </span>
                            @endif
                        </div>
                    </div>
                    <div class="form-group row">
                        <label for="testCode" class="col-sm-12 col-form-label text-md-left">
                            {{__('Code of Test')}}
                        </label>
                        <div class="col-md-12">
                            <textarea class="form-control{{ $errors->has('test-code') ? ' is-invalid' : '' }}" id="testCode"
                                cols="30" rows="5" name="form-test-code" wrap="off" style="font-family: monospace;"
                                required autofocus></textarea>
                            @if ($errors->any())
                            <span class="invalid-feedback" role="alert">
                                <strong>{{ $errors->first() }}</strong>
                            </span>
                            @endif
                        </div>
                    </div>
                    <div class="form-group row mb-0">
                        <div class="col-md-12 offset-md-12">
                            <button type="submit" class="btn btn-primary">
                                {{ __('Save Changes') }}
                            </button>

                        </div>
                    </div>
                </form>
            </div>
        </div>

        @foreach ($exercise->tests as $test)
        @include('test.test_partial', ['exercise' => $exercise, 'test' => $test])
        @endforeach
    </div>
    <div style="margin-left: 3%;" class="rounded">
        {{ $exercise->tests->links() }}
    </div>

</div>
@endsection
