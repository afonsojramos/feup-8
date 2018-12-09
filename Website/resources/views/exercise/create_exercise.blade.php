@extends('layouts.app')

@section('content')
<div class="container">
    <div class="row justify-content-center">
        <div class="col-md-12">
            <div class="list-group container">
                <div class="container d-flex w-100 justify-content-between">
                <h3 class="w-100 mb-1">{{ __('Create Exercise') }}</h3>
                @foreach ($errors->all() as $error)
                    <div class="alert alert-danger">{{ $error }} </div> 
                @endforeach
                @if (session('msg'))
                    <div class="alert alert-success">
                        {{ session('msg') }}
                    </div>
                @endif
                </div>
                <hr class="my-4 w-75">
                <div class="container d-flex w-100 justify-content-between">
                    <form method="POST" action="{{ route('/exercise/create') }}" class="w-100 list-group-item list-group-item-action flex-column align-items-start rounded mb-2 pt-3 pl-4"
                        style="margin-bottom: 2%; padding: 2rem 1rem !important;">
                        @csrf

                        <div class="form-group row">
                            <label for="title" class="col-sm-3 col-form-label text-md-right">{{ __('Exercise Title') }}</label>

                            <div class="col-md-8">
                                <input id="title" type="text" class="form-control{{ $errors->has('email') ? ' is-invalid' : '' }}" name="form-title" value="{{ old('title') }}" required autofocus>

                                @if ($errors->any())
                                    <span class="invalid-feedback" role="alert">
                                        <strong>{{ $errors->first() }}</strong>
                                    </span>
                                @endif
                            </div>
                        </div>

                        <div class="form-group row">
                            <label for="description" class="col-sm-3 col-form-label text-md-right">{{ __('Description') }}</label>

                            <div class="col-md-8">
                                
                                <textarea class="form-control{{ $errors->has('description') ? ' is-invalid' : '' }}" 
                                    id="description" rows="3" 
                                    name="form-description" value="{{ old('description') }}" required autofocus>
                                </textarea>

                                @if ($errors->any())
                                    <span class="invalid-feedback" role="alert">
                                        <strong>{{ $errors->first() }}</strong>
                                    </span>
                                @endif
                            </div>
                        </div>


                        <div class="form-group row">
                            <div class="col-md-3 offset-md-3">
                                <div class="form-check">
                                    <input class="form-check-input" type="checkbox" name="form-isPrivate" id="remember" {{ old('remember') ? 'checked' : '' }}>

                                    <label class="form-check-label" for="remember">
                                        {{ __('Private Exercise') }}
                                    </label>
                                </div>
                            </div>
                        </div>

                        <div class="form-group row mb-0">
                            <div class="col-md-2 offset-md-10" >
                                <button type="submit" class="btn btn-primary">
                                    {{ __('Create') }}
                                </button>

                            </div>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    </div>
</div>
@endsection
